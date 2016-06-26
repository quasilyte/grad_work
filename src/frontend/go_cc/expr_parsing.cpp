#include <frontend/go_cc/expr_parsing.hpp>

#include <cc/strict/arith.hpp>
#include <cc/fn_check.hpp>
#include <cc/parse_lit.hpp>
#include <ast/literals.hpp>
#include <ast/builtins.hpp>
#include <ast/defs.hpp>
#include <ast/typedefs.hpp>
#include <mn_hash.hpp>
#include <frontend/go_cc/common/reader.hpp>
#include <frontend/go_cc/common/module.hpp>
#include <lex/char_case.hpp>
#include <unit/globals.hpp>
#include <unit/scope.hpp>
#include <unit/fns.hpp>
#include <unit/structs.hpp>
#include <err/sym_errors.hpp>
#include <err/stx_errors.hpp>
#include <dev_assert.hpp>
#include <util/std_vector.hpp>
#include <deps/c/string.hpp>
#include <chars/categories.hpp>

using namespace go_cc;
using namespace chars;
using sym::Type;

ast::NodeList expr_stash;

ast::Node* parse_operand(Reader* reader);

ast::Node* parse_local(dt::StrView name) {
  auto local = unit::scope_symbol(name);

  if (local.IsVoid()) {
    auto global = unit::get_global(name);

    if (global) {
      return new ast::Var{name, global->type};
    } else {
      throw err::UndefinedSymbol{name};
    }
  } else {
    return new ast::Var{name, local};
  }
}

ast::BinaryNode binary_node(Reader* reader) {
  auto lhs = util::pop(expr_stash);
  auto rhs = parse_operand(reader->Skip());

  return ast::BinaryNode{lhs, rhs};
}

ast::Node* parse_node(Reader* reader) {
  do {
    expr_stash.push_back(parse_operand(reader));
  } while (reader->Skip()->CanRead() && ',' != reader->PeekCurrent());

  dev_assert(1 == expr_stash.size());

  return util::pop(expr_stash);
}
#include <cstdio>
ast::ArgList collect_args(Reader* reader) {
  ast::ArgList args;

  if (reader->Skip()->CanRead()) {

    for (;;) {
      auto arg = parse_node(reader->Skip());
      args.push_back(arg);

      if (reader->Skip()->CanRead()) {
        reader->MustConsume(',');
      } else {
        return args;
      }
    }
  } else {
    return args;
  }
}

/*
ast::ArgList collect_attrs(Cursor* cur) {
  ast::NodeList attrs;

  for (;;) {
    attrs.push_back(parse_expr(skip(cur, SPACES), ",}"));

    switch (read_next(cur)) {
    case '}': return attrs;
    case ',': continue;
    default: throw "unexpected!";
    }
  }
}
*/

/*
ast::Node* parse_struct_lit(dt::StrView name, Cursor* cur) {
  auto st = unit::get_struct(name);
  if (!st) {
    throw err::UndefinedType{name};
  }

  auto initializers = collect_attrs(cur);
  if (initializers.size() != st->attrs.size()) {
    throw "cant partially initialize yet";
  }

  for (uint i = 0; i < initializers.size(); ++i) {
    if (!st->attrs[i].type.SameAs(initializers[i]->Type())) {
      throw "type mismatch";
    }
  }

  return new ast::CompoundLit{std::move(initializers), st->type};
}
*/

ast::Node* parse_fn_call(Type fn_type, dt::StrView args_text) {
  Reader reader{args_text};

  auto fn = unit::get_mono_fn(fn_type);

  if (reader.Skip()->TryConsume(')')) { // 0 args
    cc::check_arity(fn, 0);
    return new ast::MonoFnCall{fn, ast::ArgList{}};
  } else {
    auto args = collect_args(&reader);
    cc::check_arity(fn, args.size());
    cc::check_arg_types(fn, args);

    return new ast::MonoFnCall{fn, std::move(args)};
  }
}

ast::Node* parse_paren_expr(Reader* reader) {
  reader->Skip(1); // Opening `(`

  while (')' != reader->Skip()->PeekCurrent()) {
    expr_stash.push_back(parse_operand(reader));
  }

  reader->Skip(1); // Closing `)`
  return util::pop(expr_stash);
}

/*
ast::Node* go_cc::parse_expr(lex::Cursor* cur, const char* terms) {
  do {
    expr_stash.push_back(parse_operand(cur));
  } while (nullptr == strchr(terms, at(skip(cur, HOR_SPACES))));

  dev_assert(1 == expr_stash.size());  

  return util::pop(expr_stash);
}
*/

ast::Node* go_cc::parse_expr(dt::StrView input) {
  Reader reader{input};

  do {
    expr_stash.push_back(parse_operand(&reader));
  } while (reader.Skip()->CanRead());

  dev_assert(1 == expr_stash.size());

  return util::pop(expr_stash);
}

ast::Node* parse_word(Reader* reader) {
  using namespace mn_hash;

  auto name = reader->Skip()->Read(C_IDENT);
  auto hash = mn_hash::encode9(name.Data(), name.Len());

  switch (hash) {
  case "return"_m9:
    throw err::SyntaxError{"return", "expr"};
  case "if"_m9:
    throw err::SyntaxError{"if", "expr"};

  default:
    auto symbol = get_module_symbol(name);

    if (symbol.IsMonoFn() && '(' == reader->PeekCurrent()) {
      return parse_fn_call(symbol, reader->ReadGroup('(', ')'));
    } else {
      return new ast::Var{name, symbol};
    }

    // return parse_local(name);

  /*
  default:
    switch (reader->PeekCurrent()) {
    case '(': return parse_fn_call(name, reader->Skip(1));
    case '{': return parse_struct_lit(name, reader->Skip(1));
    default: return parse_local(name);
    }
    */
  }

}

ast::Node* parse_operand(Reader* reader) {
  auto reader_copy = *reader;

  switch (reader->PeekCurrent()) {
  case '+': return cc::strict_sum(binary_node(reader->Skip(1)));
  case '*': return cc::strict_mul(binary_node(reader->Skip(1)));
  case '/': return cc::strict_div(binary_node(reader->Skip(1)));
  case '-': return cc::strict_sub(binary_node(reader->Skip(1)));
  case '=':
    switch (reader->PeekNext()) {
    case '=': return cc::strict_eq(binary_node(reader->Skip(2)));
    default:
      throw "tokenizer error";
      // throw err::UnexpectedToken{{'=', reader->PeekNext()}};
    }

  case '"': return cc::parse_str(reader);
  case '>': return new ast::NumGt{binary_node(reader->Skip(1))};
  case '<': return new ast::NumLt{binary_node(reader->Skip(1))};
  case '(': return parse_paren_expr(reader);
  case DIGIT_RANGE: return cc::parse_num(reader);
  case LETTER_RANGE: return parse_word(reader);

  default:
    printf("at `%c`\n", reader_copy.PeekCurrent());
    throw "unexpected expr";
  }
}
