#include <cc/parse_lit.hpp>

#include <lex/num_tagger.hpp>
#include <lex/reader.hpp>
#include <ast/literals.hpp>

using namespace lex;

ast::Node* cc::parse_num(Reader* reader) {
  auto num = reader->ReadToken<NumTagger>();

  switch (num.tag) {
  case NumTagger::INT:
    return new ast::Int{dt::StrView{num.data, num.len}};

  case NumTagger::REAL:
    return new ast::Real{dt::StrView{num.data, num.len}};

  default: throw "ParseExpr: malformed numeric literal";
  }
}

ast::Node* cc::parse_str(Reader* reader) {
  return new ast::Str{reader->ReadLiteral('"')};
}
