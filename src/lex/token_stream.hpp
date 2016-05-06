#pragma once

#include "lex/token.hpp"

namespace lex {
  class TokenStream;
}

class lex::TokenStream {
public:
  struct UnexpectedRparen{};

  TokenStream(const char* input, usize input_len);
  TokenStream(Token);

  void next() noexcept;

  Token next_token() noexcept;
  Token::Tag next_tag() noexcept;

  Token current_token() const noexcept;
  Token::Tag current_tag() const noexcept;

private:
  const char* input_end;
  Token tok;

  void consume_spaces() noexcept;

  void eval() noexcept;
  void eval_number() noexcept;
  void eval_str() noexcept;
  void eval_word() noexcept;
  void eval_list() noexcept;

  char current_char() const noexcept;
  bool has_more_input() const noexcept;

  void collect_digits() noexcept;
  void collect_str() noexcept;
};

static_assert(
  sizeof(lex::TokenStream) == 24 || sizeof(lex::TokenStream) == 16,
  "type size expectations failed"
);
