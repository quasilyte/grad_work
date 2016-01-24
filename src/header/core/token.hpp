#pragma once

enum TokenTag {
  /**
    * Value qualified:
    */
  WORD,
  DECIMAL,
  /**
    * Identity qualified:
    */
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
  /**
    * M4 hash qualified:
    */
  PLUS = 43, // +
  PLUS2 = 5547, // ++
  MINUS = 45, // -
  MINUS2 = 5805, // --
  EQ = 61, // =
  EQ2 = 7869, // ==
  EQ3 = 1007293, // ===
  ARROW = 5805, // ->
  SINGLE_QUOTE = 39, // ' 
  BACK_QUOTE = 96, // `
  DOT = 46, // .
  COMMA = 44, // ,
  STAR = 42, // *
  SLASH = 47, // /
  BANG = 33, // !
  AMP = 38, // &
  AMP2 = 4902, // &&
};

struct Token {
  TokenTag tag;
  const char *val;

  void init(TokenTag tag, const char *const val) {
    this->tag = tag;
    this->val = val;
  }

  static Token from_tag(TokenTag tag) {
    return (Token) {
      tag, nullptr
    };
  }
};
