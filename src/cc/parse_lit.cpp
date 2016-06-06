#include <cc/parse_lit.hpp>

#include <lex/num_tagger.hpp>
#include <lex/cursor.hpp>
#include <ast/literals.hpp>

using namespace lex;

ast::Node* cc::parse_num(Cursor* cur) {
  auto num = read_token(cur, NumTagger::Run);

  switch (num.tag) {
  case NumTagger::INT:
    return new ast::Int{dt::StrView{num.data, num.len}};

  case NumTagger::REAL:
    return new ast::Real{dt::StrView{num.data, num.len}};

  default: throw "ParseExpr: malformed numeric literal";
  }
}

ast::Node* cc::parse_str(Cursor* cur) {
  return new ast::Str{read_group(cur, '"')};
}
