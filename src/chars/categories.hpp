#pragma once

#include <chars/alphabet.hpp>

namespace chars {
  extern Alphabet SPACES;
  extern Alphabet DIGITS;
  extern Alphabet LETTERS;
  extern Alphabet C_IDENT;

  void init_spaces();
  void init_digits();
  void init_letters();
  void init_c_ident();
}
