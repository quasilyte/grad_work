#include <chars/categories.hpp>

#include <rodata/cstrings.hpp>

using namespace chars;

Alphabet chars::SPACES;
Alphabet chars::DIGITS;
Alphabet chars::LETTERS;
Alphabet chars::C_IDENT;

void chars::init_spaces() {
  SPACES = Alphabet::FromWhitelist(" \t\v\n\r");
}

void chars::init_digits() {
  DIGITS = Alphabet::FromWhitelist(rodata::DIGITS);
}

void chars::init_letters() {
  LETTERS = Alphabet::FromWhitelist(rodata::LETTERS);
}

void chars::init_c_ident() {
  C_IDENT = Alphabet::FromWhitelist(rodata::C_IDENT);
}
