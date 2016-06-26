#pragma once

#include <chars/categories.hpp>

void init_char_categories() {
  chars::init_c_ident();
  chars::init_digits();
  chars::init_letters();
  chars::init_spaces();
}
