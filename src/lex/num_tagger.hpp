#pragma once

#include <typedefs.hpp>

namespace lex {
  struct NumTagger;
  class Reader;
}

struct lex::NumTagger {
  enum: u32 {INT, REAL, MALFORMED};
  static u32 Run(Reader*);
};
