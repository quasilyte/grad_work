#include <frontend/go_cc/parsing.hpp>

#include <frontend/go_cc/expr_parsing.hpp>
#include <frontend/go_cc/stmt_parsing.hpp>
#include <frontend/go_cc/common/reader.hpp>
#include <mn_hash.hpp>

using namespace chars;

ast::Node* go_cc::parse(Reader* reader) {
  using namespace mn_hash;

  auto word = reader->Read(C_IDENT);

  // If it is a keyword, most likely we need to parse a statement
  switch (encode9(word.Data(), word.Len())) {
  case "return"_m9: return parse_return(reader);
  case "if"_m9: return parse_if(reader);

  default:
    // It can be a statement like `x := 10` or `x++`
    switch (reader->Skip()->PeekCurrent()) {
    case '=':
      return parse_assignment(word, reader->Skip(1));

    case ':':
      // [goto label] | [short assignment]
      if ('=' == reader->PeekNext()) {
        return parse_short_var_decl(word, reader->Skip(2));
      } else {
        throw "cant parse goro labels yet";
      }
      break;

    case '+':
      // [x++] | [x+=] | [x+expr]
      switch (reader->PeekNext()) {
      case '+': throw "no postfix ++";
      case '=':
        return parse_plus_assignment(word, reader->Skip(2));
      }
      break;

    default:
      throw "cant parse expr";
      // return parse_expr(cur, ";\n");
    }
  }

  throw "parse: unexpected end of fn";
}
