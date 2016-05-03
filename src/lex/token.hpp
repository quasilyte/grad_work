#pragma once

#include "typedefs.hpp"
#include "m_hash.hpp"

namespace lex {
  using namespace m_hash;
  
  enum Tag: u32 {
    /**
     * Value qualified:
     */
    WORD,
      INTEGER,
      REAL,
      STR,
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
      PLUS = encode4("+"),
      PLUS2 = encode4("++"),
      PLUS_EQ = encode4("+="),
      MINUS = encode4("-"),
      MINUS2 = encode4("--"),
      MINUS_EQ = encode4("-="),
      ARROW = encode4("->"),
      EQ = encode4("="),
      EQ2 = encode4("=="),
      EQ3 = encode4("==="),
      FAT_ARROW = encode4("=>"),
      DOT = encode4("."),
      DOT2 = encode4(".."),
      DOT3 = encode4("..."),
      STAR = encode4("*"),
      SLASH = encode4("/"),
      SLASH2 = encode4("//"),
      AMP = encode4("&"),
      AMP2 = encode4("&&")
  };

  struct Token;
}

struct lex::Token {
  const char *value;
  Tag tag;
  usize len;

  Token(Tag tag, const char *value, usize len);
  Token(Tag tag, const char *value);

  real fetch_real() const;
  integer fetch_integer() const;
  
  u64 hash_value() const;
};
