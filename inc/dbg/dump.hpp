#pragma once

#include <cstdio>

#include <lexer/token.hpp>

inline void dump_token(Token *tok) {
#define VALUE_CASE(tag) \
  case tag: std::printf(#tag " `%.*s`\n", tok->len, tok->value); break;
#define CASE(tag) \
  case tag: std::printf("<%s>\n", #tag); break

  // Generated with `script/tokens_dump_labels.awk`
  switch (tok->tag) {
  VALUE_CASE(WORD);
  VALUE_CASE(DECIMAL);
  VALUE_CASE(REAL);
  CASE(SOURCE_END);
  CASE(LPAREN);
  CASE(RPAREN);
  CASE(LBRACE);
  CASE(RBRACE);
  CASE(LBRACKET);
  CASE(RBRACKET);
  CASE(HASH);
  CASE(DOLLAR);
  CASE(BACKSLASH);
  CASE(COLON);
  CASE(SEMICOLON);
  CASE(AT);
  CASE(QUES);
  CASE(CARET);
  CASE(PIPE);
  CASE(TILDE);
  CASE(LT);
  CASE(GT);
  CASE(UNDERSCORE);
  CASE(PERCENT);
  CASE(BACK_QUOTE);
  CASE(QUOTE);
  CASE(COMMA);
  CASE(BANG);
  CASE(PLUS);
  CASE(PLUS2);
  CASE(PLUS_EQ);
  CASE(MINUS);
  CASE(MINUS2);
  CASE(MINUS_EQ);
  CASE(ARROW);
  CASE(EQ);
  CASE(EQ2);
  CASE(EQ3);
  CASE(FAT_ARROW);
  CASE(DOT);
  CASE(DOT2);
  CASE(DOT3);
  CASE(STAR);
  CASE(SLASH);
  CASE(SLASH2);
  CASE(AMP);
  default:
    printf("unknown tag %d!\n", tok->tag);
    abort();
  }

#undef VALUE_CASE
#undef CASE
}
