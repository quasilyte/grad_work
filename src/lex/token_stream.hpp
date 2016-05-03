#pragma once

#include "typedefs.hpp"
#include "token.hpp"

namespace lex {
  class TokenStream;
}

class lex::TokenStream {
public:
  class NonPrintableCharError{};
  
  TokenStream(const char *input, usize len):
  token{SOURCE_END, input, 0}, end{input + len} {}

  TokenStream(Token *tok):
  token{SOURCE_END, tok->value, 0}, end{tok->value + tok->len - 1} {}

  void next() noexcept;
  const Token& next_token() noexcept;
  Tag next_tag() noexcept;
  const Token& current() const noexcept;
  Tag current_tag() const noexcept;
  
private:
  Token token;
  const char *const end;

  void eval() noexcept;
  void eval_word() noexcept;
  void eval_str() noexcept;
  void eval_number() noexcept;
  void eval_op() noexcept;
  
  void collect_digits() noexcept;
  void consume_spaces() noexcept;
  char current_char() const noexcept; 
};
	     

