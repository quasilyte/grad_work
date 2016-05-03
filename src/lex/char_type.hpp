#pragma once

namespace lex {
  bool is_space(char); // \s
  bool not_space(char); // \S
  bool is_alpha(char); // [a-zA-Z]
  bool is_digit(char); // \d
  bool is_word(char); // \w
}
