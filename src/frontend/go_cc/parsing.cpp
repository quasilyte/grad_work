#include <frontend/go_cc/parsing.hpp>

#include <lex/cursor.hpp>
#include <frontend/go_cc/char_groups.hpp>
#include <frontend/go_cc/expr_parsing.hpp>
#include <frontend/go_cc/stmt_parsing.hpp>
#include <mn_hash.hpp>

using namespace lex;

ast::Node* go_cc::parse(Cursor* cur) {
  using namespace mn_hash;

  auto word = read(cur, IDENT);

  // If it is a keyword, most likely we need to parse a statement
  switch (encode9(word.Data(), word.Len())) {
  case "return"_m9: return parse_return(cur);
  case "if"_m9: return parse_if(cur);

  default:
    // It can be a statement like `x := 10` or `x++`
    switch (at(skip(cur, SPACES))) {
    case ':':
      // [goto label] | [short assignment]
      if ('=' == peek(cur)) {
        return parse_short_var_decl(word, skip(cur, 2));
      } else {
        throw "cant parse goro labels yet";
      }
      break;

    case '+':
      // [x++] | [x+=] | [x+expr]
      switch (peek(cur)) {
      case '+': throw "no postfix ++";
      case '=':
        return parse_plus_assignment(word, skip(cur, 2));
      }
      break;

    default:
      return parse_expr(cur, ";\n");
    }
  }

  throw "parse: unexpected end of fn";
}
