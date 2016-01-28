#pragma once

#include <cstdio>

#include "lexer/token_stream.hpp"
#include "lexer/token.hpp"

inline void dump_token(Token *tok, int depth = 0) {
#define VALUE_CASE(tag) \
  case tag: std::printf("%*s" #tag " `%.*s`\n", depth, "", tok->len, tok->value); break;
#define CASE(tag) \
  case tag: std::printf("%*s<%s>\n", depth, "", #tag); break;
#define GROUP_CASE(tag)                         \
   case tag:                                    \
   { TokenStream ts{tok};                       \
     std::printf("%*s" #tag ":\n", depth, "");  \
     while (SOURCE_END != ts.next_tag()) {      \
       dump_token(ts.current(), depth + 2);     \
     }                                          \
   } break;



  // Generated with `script/tokens_dump_labels.awk`
  switch (tok->tag) {
  VALUE_CASE(WORD);
  VALUE_CASE(DECIMAL);
  VALUE_CASE(REAL);
  CASE(SOURCE_END);
  GROUP_CASE(PAREN_GROUP);
  CASE(LPAREN);
  CASE(RPAREN);
  GROUP_CASE(BRACE_GROUP);
  CASE(LBRACE);
  CASE(RBRACE);
  GROUP_CASE(BRACKET_GROUP);
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
