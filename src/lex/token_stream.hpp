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

  void Next() noexcept;

  Token NextToken() noexcept;
  enum Token::Tag NextTag() noexcept;

  Token CurrentToken() const noexcept;
  enum Token::Tag CurrentTag() const noexcept;

private:
  const char* input_end;
  Token tok;

  void ConsumeSpaces() noexcept;

  void Eval() noexcept;
  void EvalNumber() noexcept;
  void EvalStr() noexcept;
  void EvalWord() noexcept;
  void EvalList() noexcept;

  char CurrentChar() const noexcept;
  bool HasMoreInput() const noexcept;

  void CollectDigits() noexcept;
  void CollectStr() noexcept;
};

static_assert(
  sizeof(lex::TokenStream) == 24 || sizeof(lex::TokenStream) == 16,
  "type size expectations failed"
);
