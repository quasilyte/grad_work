#include "frontend/go_cc/classifier.hpp"

#include "mn_hash.hpp"
#include "dbg/dt.hpp"
#include "unit/globals.hpp"
#include "sym/type.hpp"
#include "ast/literals.hpp"
#include "ast/defs.hpp"
#include <cstring>
#include <cstdio>
#include "frontend/go_cc/char_groups.hpp"
#include "frontend/go_cc/types.hpp"
#include "frontend/go_cc/cursor_ext.hpp"

using namespace go_cc;
using namespace lex;
using sym::Type;

TopLevel Classifier::Run(const char* input_cstr) {
  Classifier self{input_cstr};
  return self.Classify();
}

Classifier::Classifier(const char* input_cstr): cur{lex::Cursor{input_cstr}} {}

TopLevel Classifier::Classify() {
  using mn_hash::operator "" _m9;

  while (lex::can_read(lex::skip(&cur, SPACES))) {
    auto keyword = lex::read_m9(&cur, IDENT);

    switch (keyword) {
    case "var"_m9: ClassifyVar(); break;
    case "func"_m9: ClassifyFn(); break;

    default:

      throw "invalid top level declaration";
    }
  }

  return result;
}



/*
ast::Node* parse_token(lex::Token tok) {
  switch (tok.Tag()) {
  case Token::INT:
    return new ast::Int{tok};
  case Token::REAL:
    return new ast::Real{tok};
  case Token::STR:
    return new ast::Str{tok};

  case Token::LIST:
    throw "cant parse list yet";

  default:
    throw "parse_token: unexpected token";
  }
}
*/

/*
        func sum (x int, y int) int {
          return x + y
        }
*/

void Classifier::ClassifyFn() {
  auto name = next_ident(&cur);
  auto params = read_group(skip(&cur, SPACES), '(', ')').Truncate(1);
  auto ret_type_name = next_ident(&cur);
  auto body = read_group(skip(&cur, SPACES), '{', '}').Truncate(1);

  auto ret_type = ret_type_name.IsEmpty()
      ? sym::Type::Void()
      : type_by_name(ret_type_name);

  result.fns.push_back(FnDecl{name, params, body, ret_type});
}

void Classifier::ClassifyVar() {
  auto name = next_ident(&cur);

  if (try_consume(skip(&cur, SPACES), '=')) {
    result.globals.push_back(Decl{name, next_expr(&cur)});
  } else {
    auto type = type_by_name(next_ident(&cur));

    if (try_consume(skip(&cur, SPACES), '=')) {
      result.typed_globals.push_back(
        TypedDecl{name, type, next_expr(&cur)}
      );
    } else {
      throw "expected `=` token";
    }
  }
  /*
  auto maybeType = toks.NextToken();

  if (maybeType.Is(EQ)) {
    puts("decl");
    auto expr = toks.NextToken();

    result.globals.push_back(
      Decl{name, expr}
    );

  } else {
    puts("typed decl");
    auto eq = toks.NextToken();
    auto expr = toks.NextToken();

    result.typed_globals.push_back(
      TypedDecl{name, type_by_name(maybeType), expr}
    );
  }
  */
}
