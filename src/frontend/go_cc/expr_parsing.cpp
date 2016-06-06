#include <frontend/go_cc/expr_parsing.hpp>

#include <cc/strict_arith.hpp>
#include <cc/fn_check.hpp>
#include <cc/parse_lit.hpp>
#include <ast/literals.hpp>
#include <ast/builtins.hpp>
#include <ast/defs.hpp>
#include <ast/typedefs.hpp>
#include <mn_hash.hpp>
#include <frontend/go_cc/cursor_ext.hpp>
#include <frontend/go_cc/char_groups.hpp>
#include <lex/char_case.hpp>
#include <lex/cursor.hpp>
#include <unit/globals.hpp>
#include <unit/scope.hpp>
#include <unit/fns.hpp>
#include <unit/structs.hpp>
#include <errors.hpp>
#include <dev_assert.hpp>
#include <util/std_vector.hpp>
#include <deps/c/string.hpp>

using namespace go_cc;
using namespace lex;

ast::NodeList expr_stash;

ast::Node* parse_operand(Cursor* cur);

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

ast::BinaryNode binary_node(Cursor* cur) {
  auto lhs = util::pop(expr_stash);
  auto rhs = parse_operand(skip(cur, SPACES));

  return ast::BinaryNode{lhs, rhs};
}

ast::ArgList collect_args(Cursor* cur) {
  ast::ArgList args;

  for (;;) {
    args.push_back(parse_expr(skip(cur, SPACES), ",)"));

    switch (read_next(cur)) {
    case ')': return args;
    case ',': continue;
    default: throw "unexpected!";
    }
  }
}

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

ast::Node* parse_fn_call(dt::StrView name, Cursor* cur) {
  auto fn = unit::get_mono_fn(name);

  if (!fn) {
    throw err::UndefinedSymbol{name};
  }

  if (try_consume(skip(cur, SPACES), ')')) { // 0 args
    cc::check_arity(fn, ast::ArgList{});

    return new ast::MonoFnCall{fn, ast::ArgList{}};
  } else {
    auto args = collect_args(cur);
    cc::check_arity(fn, args);
    cc::check_arg_types(fn, args);

    return new ast::MonoFnCall{fn, std::move(args)};
  }
}

ast::Node* parse_paren_expr(Cursor* cur) {
  skip(cur, 1); // Opening `(`

  while (')' != at(skip(cur, SPACES))) {
    expr_stash.push_back(parse_operand(cur));
  }

  skip(cur, 1); // Closing `)`
  return util::pop(expr_stash);
}

ast::Node* go_cc::parse_expr(lex::Cursor* cur, const char* terms) {
  do {
    expr_stash.push_back(parse_operand(cur));
  } while (nullptr == strchr(terms, at(skip(cur, HOR_SPACES))));

  dev_assert(1 == expr_stash.size());  

  return util::pop(expr_stash);
}

ast::Node* go_cc::parse_expr(Cursor cur) {
  do {
    expr_stash.push_back(parse_operand(&cur));
  } while (can_read(skip(&cur, SPACES)));

  dev_assert(1 == expr_stash.size());

  return util::pop(expr_stash);
}

ast::Node* parse_word(Cursor* cur) {
  using namespace mn_hash;

  auto name = next_ident(cur);
  auto hash = mn_hash::encode9(name.Data(), name.Len());

  switch (hash) {
  case "return"_m9:
    throw err::UnexpectedKeyword{"return", "expr"};
  case "if"_m9:
    throw err::UnexpectedKeyword{"if", "expr"};

  default:
    switch (at(cur)) {
    case '(': return parse_fn_call(name, skip(cur, 1));
    case '{': return parse_struct_lit(name, skip(cur, 1));
    default: return parse_local(name);
    }
  }
}

ast::Node* parse_operand(Cursor* cur) {
  auto cur_copy = *cur;

  switch (at(cur)) {
  case '+': return cc::strict_sum(binary_node(skip(cur, 1)));
  case '*': return cc::strict_mul(binary_node(skip(cur, 1)));
  case '/': return cc::strict_div(binary_node(skip(cur, 1)));
  case '-': return cc::strict_sub(binary_node(skip(cur, 1)));
  case '=':
    switch (peek(cur)) {
    case '=': return cc::strict_eq(binary_node(skip(cur, 2)));
    default:
      throw err::UnexpectedToken{{'=', peek(cur)}};
    }

  case '"': return cc::parse_str(cur);
  case '>': return new ast::NumGt{binary_node(skip(cur, 1))};
  case '<': return new ast::NumLt{binary_node(skip(cur, 1))};
  case '(': return parse_paren_expr(cur);
  case DIGIT_RANGE: return cc::parse_num(cur);
  case LETTER_RANGE: return parse_word(cur);

  default:
    printf("`%s` at `%c`\n", cur_copy.pos, at(&cur_copy));
    throw "unexpected expr";
  }
}
