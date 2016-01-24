#pragma once

#include "typedefs.hpp"
#include "parse_val.hpp"

inline constexpr u32 m4_hash(const char *cstr, u32 hash = 0) {
  return *cstr ? (hash << 7) + m4_hash(cstr + 1, *cstr) : hash;
}

enum TokenTag {
  /**
    * Value qualified:
    */
  WORD,
  DECIMAL,
  REAL,
  /**
    * Identity qualified:
    */
  SOURCE_END,
  LPAREN, // (
  RPAREN, // )
  LBRACE, // {
  RBRACE, // }
  LBRACKET, // [
  RBRACKET, // ]
  HASH, // #
  DOLLAR, // $
  BACKSLASH,
  COLON, // :
  SEMICOLON, // ;
  AT, // @
  QUES, // ?
  CARET, // ^
  PIPE, // |
  TILDE, // ~
  LT, // <
  GT, // >
  UNDERSCORE, // _
  PERCENT, // %
  BACK_QUOTE, // `
  QUOTE, // '
  COMMA, // ,
  BANG, // !
  /**
    * M4 hash qualified:
    */
  PLUS = m4_hash("+"),
  PLUS2 = m4_hash("++"),
  PLUS_EQ = m4_hash("+="),
  MINUS = m4_hash("-"),
  MINUS2 = m4_hash("--"),
  MINUS_EQ = m4_hash("-="),
  ARROW = m4_hash("->"),
  EQ = m4_hash("="),
  EQ2 = m4_hash("=="),
  EQ3 = m4_hash("==="),
  FAT_ARROW = m4_hash("=>"),
  DOT = m4_hash("."),
  DOT2 = m4_hash(".."),
  DOT3 = m4_hash("..."),
  STAR = m4_hash("*"),
  SLASH = m4_hash("/"),
  SLASH2 = m4_hash("//"),
  AMP = m4_hash("&"),
  AMP2 = m4_hash("&&")
};

struct Token {
  const char* value;
  int len;
  TokenTag tag;

  real fetch_real() const {
    return parse_real(value);
  }

  decimal fetch_decimal() const {
    return parse_decimal(value);
  }
};
