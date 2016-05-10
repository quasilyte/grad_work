#pragma once

#include "lex/token_stream.hpp"
#include <vector>

namespace cc {
  struct TopLevel;
}

struct cc::TopLevel {
  std::vector<lex::Token> exprs;
  std::vector<lex::TokenStream> funcs;
  std::vector<lex::TokenStream> globals;
};
