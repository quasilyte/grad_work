#include "lex/token_stream.hpp"

#include "dev_assert.hpp"
#include "lex/char_type.hpp"

using namespace lex;

TokenStream::TokenStream(const char* input, usize input_len):
input_end{input + input_len},
tok{Token::SOURCE_END, input, 0} {}

lex::TokenStream::TokenStream(Token tok):
input_end{tok.Val() + tok.Len() - 1},
tok{Token::SOURCE_END, tok.Val(), 0} {}

void TokenStream::Next() noexcept {
  tok.val += tok.len;
  ConsumeSpaces();

  if (tok.val == input_end) {
    tok.tag = Token::SOURCE_END;
  } else {
    Eval();
  }
}

Token TokenStream::NextToken() noexcept {
  Next();
  return tok;
}

enum Token::Tag TokenStream::NextTag() noexcept {
  Next();
  return tok.tag;
}

Token TokenStream::CurrentToken() const noexcept {
  return tok;
}

enum Token::Tag TokenStream::CurrentTag() const noexcept {
  return tok.tag;
}

void TokenStream::ConsumeSpaces() noexcept {
  while (is_space(*tok.val)) {
    tok.val += 1;
  }
}

void TokenStream::Eval() noexcept {
  dev_assert(tok.val < input_end);

  tok.len = 1;

  switch (*tok.val) {
  case '"': EvalStr(); break;
  case '(': EvalList(); break;
  case ')': throw UnexpectedRparen{};
  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9': EvalNumber(); break;
  default: EvalWord();
  }
}

void TokenStream::EvalNumber() noexcept {
  CollectDigits();

  if ('.' == CurrentChar()) {
    tok.len += 1; // Pass over dot
    CollectDigits();
    tok.tag = Token::REAL;
  } else {
    tok.tag = Token::INT;
  }
}

void TokenStream::EvalStr() noexcept {
  while ('"' != CurrentChar()) {
    tok.len += 1;
  }

  tok.len += 1; // Pass over closing '"'
  tok.tag = Token::STR;
}

void TokenStream::EvalWord() noexcept {
  // We enter this loop after passing first alpha char,
  // so no need to handle it (tok.len = 1, so it is not checked).
  while (HasMoreInput()
         && not_space(CurrentChar())
         && '(' != CurrentChar()
         && ')' != CurrentChar()
         && '"' != CurrentChar()) {
    tok.len += 1;
  }

  tok.tag = Token::WORD;
}

void TokenStream::EvalList() noexcept {
  int depth = 0;

  while (!(')' == CurrentChar() && 0 == depth)) {
    switch (CurrentChar()) {
    case '(':
      depth += 1;
      tok.len += 1;
      break;

    case ')':
      depth -= 1;
      tok.len += 1;
      break;

    case '"':
      CollectStr();
      break;

    default: tok.len += 1;
    }
  }

  tok.val += 1; // No need for leading '('
  tok.tag = Token::LIST;
}

char TokenStream::CurrentChar() const noexcept {
  return tok.val[tok.len];
}

bool TokenStream::HasMoreInput() const noexcept {
  return tok.val + tok.len < input_end;
}

void TokenStream::CollectDigits() noexcept {
  while (is_digit(CurrentChar())) {
    tok.len += 1;
  }
}

void TokenStream::CollectStr() noexcept {
  while ('"' != CurrentChar()) {
    tok.len += 1;
  }

  tok.len += 1; // Pass over closing '"'
}
