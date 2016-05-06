#include "lex/token_stream.hpp"

#include "dev_assert.hpp"
#include "lex/char_type.hpp"

using namespace lex;

TokenStream::TokenStream(const char* input, usize input_len):
input_end{input + input_len},
tok{Token::SOURCE_END, input, 0} {}

lex::TokenStream::TokenStream(Token tok):
input_end{tok.get_val() + tok.get_len() - 1},
tok{Token::SOURCE_END, tok.get_val(), 0} {}

void TokenStream::next() noexcept {
  tok.val += tok.len;
  consume_spaces();

  if (tok.val == input_end) {
    tok.tag = Token::SOURCE_END;
  } else {
    eval();
  }
}

Token TokenStream::next_token() noexcept {
  next();
  return tok;
}

Token::Tag TokenStream::next_tag() noexcept {
  next();
  return tok.tag;
}

Token TokenStream::current_token() const noexcept {
  return tok;
}

Token::Tag TokenStream::current_tag() const noexcept {
  return tok.tag;
}

void TokenStream::consume_spaces() noexcept {
  while (is_space(*tok.val)) {
    tok.val += 1;
  }
}

void TokenStream::eval() noexcept {
  dev_assert(tok.val < input_end);

  tok.len = 1;

  switch (*tok.val) {
  case '"': eval_str(); break;
  case '(': eval_list(); break;
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
  case '9': eval_number(); break;
  default: eval_word();
  }
}

void TokenStream::eval_number() noexcept {
  collect_digits();

  if ('.' == current_char()) {
    tok.len += 1; // Pass over dot
    collect_digits();
    tok.tag = Token::REAL;
  } else {
    tok.tag = Token::INT;
  }
}

void TokenStream::eval_str() noexcept {
  while ('"' != current_char()) {
    tok.len += 1;
  }

  tok.len += 1; // Pass over closing '"'
  tok.tag = Token::STR;
}

void TokenStream::eval_word() noexcept {
  // We enter this loop after passing first alpha char,
  // so no need to handle it (tok.len = 1, so it is not checked).
  while (has_more_input()
         && not_space(current_char())
         && '(' != current_char()
         && ')' != current_char()
         && '"' != current_char()) {
    tok.len += 1;
  }

  tok.tag = Token::WORD;
}

void TokenStream::eval_list() noexcept {
  int depth = 0;

  while (!(')' == current_char() && 0 == depth)) {
    switch (current_char()) {
    case '(':
      depth += 1;
      tok.len += 1;
      break;

    case ')':
      depth -= 1;
      tok.len += 1;
      break;

    case '"':
      collect_str();
      break;

    default: tok.len += 1;
    }
  }

  tok.val += 1; // No need for leading '('
  tok.tag = Token::LIST;
}

char TokenStream::current_char() const noexcept {
  return tok.val[tok.len];
}

bool TokenStream::has_more_input() const noexcept {
  return tok.val + tok.len < input_end;
}

void TokenStream::collect_digits() noexcept {
  while (is_digit(current_char())) {
    tok.len += 1;
  }
}

void TokenStream::collect_str() noexcept {
  while ('"' != current_char()) {
    tok.len += 1;
  }

  tok.len += 1; // Pass over closing '"'
}
