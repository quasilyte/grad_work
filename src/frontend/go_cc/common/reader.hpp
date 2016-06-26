#pragma once

#include <lex/reader.hpp>
#include <sym/type.hpp>

namespace go_cc {
  class Reader;
}

class go_cc::Reader: public lex::Reader {
public:
  using lex::Reader::Reader;

  dt::StrView ReadGroup(char open, char close);
  dt::StrView ReadExpr();
  sym::Type ReadType();

  Reader* Skip(chars::Alphabet to_skip = chars::SPACES);
  Reader* Skip(uint n);
};
