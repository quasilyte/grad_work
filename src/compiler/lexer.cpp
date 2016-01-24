#include "lexer.hpp"

#include <ctype.h>

using namespace compiler;

struct Arr {
  char *mem;
  size_t cap;
};


/*
9 = \t
A = \n
D = \r
C = \f
20 = \s */
bool is_space(char ch) {
  return (((((1L << 0x0009) |
	     (1L << 0x000A) |
	     (1L << 0x000B) |
	     (1L << 0x000C) |
	     (1L << 0x000D) |
	     (1L << 0x0020)) >> ch) & 1L) != 0);
}

bool is_alpha(char ch) {
  return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

bool is_digit(char ch) {
  return ch >= '0' && ch <= '9';
}

void Lexer::skip_spaces() {
  while (is_space(*pos)) {
    ++pos;
  }
}

void Lexer::fetch_byte() {
  if (is_space(*pos)) {
    char *addr = pos;
    skip_spaces();
    *addr = '\0';
    fetched_byte = *pos;
  } else {
    fetched_byte = *pos;
    *pos = '\0';
    skip_spaces();
  }
}

void Lexer::fetch_word(Token *token) {
  token->init(WORD, pos);
  while (is_alpha(*++pos)) {}
  fetch_byte();
}

void Lexer::fetch_num(Token *token) {
  token->init(DECIMAL, pos);
  while (is_digit(*++pos)) {}
  fetch_byte();
}

void Lexer::fetch_op(Token *token) {
  #define HANDLE(OP) case OP: token->tag = OP; break;
  
  uint hash = static_cast<uint>(*pos++);
  while (!is_space(*pos)) {
    hash <<= 7;
    hash += static_cast<uint>(*pos++);
  }

  skip_spaces();
  fetched_byte = *pos;

  // Select and return op token
  switch (hash) {
    HANDLE(PLUS);
    HANDLE(PLUS2);
    HANDLE(MINUS);
    HANDLE(MINUS2);
  default:
    throw new int(10);
  }
  #undef HANDLE
}

Lexer::Lexer(char *input, size_t len) {
  this->pos = input;
  this->max_pos = input + len;
  skip_spaces();
  fetched_byte = *pos;
}

#include <cstdio>
Token Lexer::next() {
#define EMIT(TAG) token.tag = TAG; \
  ++pos;			    \
  skip_spaces();		    \
  fetched_byte = *pos;		    \
  return token;
  Token token;

  /*
  switch ((unsigned char) fetched_byte) {
  case 0u: 
  case 1u: 
  case 2u: 
  case 3u: 
  case 4u: 
  case 5u: 
  case 6u: 
  case 7u: 
  case 8u: 
  case 9u: 
  case 10u: 
  case 11u: 
  case 12u: 
  case 13u: 
  case 14u: 
  case 15u: 
  case 16u: 
  case 17u: 
  case 18u: 
  case 19u: 
  case 20u: 
  case 21u: 
  case 22u: 
  case 23u: 
  case 24u: 
  case 25u: 
  case 26u: 
  case 27u: 
  case 28u: 
  case 29u: 
  case 30u: 
  case 31u: 
  case 32u: ++pos; break;
  case '!': EMIT(BANG);
  case '"': ++pos; break;
  case '#': EMIT(HASH);
  case '$': EMIT(DOLLAR);
  case '%': EMIT(PERCENT);
  case '&': EMIT(AMP);
  case '\'': EMIT(SINGLE_QUOTE);
  case '(': EMIT(LPAREN);
  case ')': EMIT(RPAREN);
  case '*': EMIT(STAR);
  case '+': fetch_op(&token); break;
  case ',': EMIT(COMMA);
  case '-': fetch_op(&token); break;
  case '.': EMIT(DOT);
  case '/': EMIT(SLASH);
  case '0': 
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9': fetch_num(&token); break;
  case ':': EMIT(COLON);
  case ';': EMIT(SEMICOLON);
  case '<': EMIT(LT);
  case '=': EMIT(EQ);
  case '>': EMIT(GT);
  case '?': EMIT(QUES);
  case '@': EMIT(AT);
  case 'A': 
  case 'B':
  case 'C':
  case 'D':
  case 'E':
  case 'F':
  case 'G':
  case 'H':
  case 'I':
  case 'J':
  case 'K':
  case 'L':
  case 'M':
  case 'N':
  case 'O':
  case 'P':
  case 'Q':
  case 'R':
  case 'S':
  case 'T':
  case 'U':
  case 'V':
  case 'W':
  case 'X':
  case 'Y':
  case 'Z': fetch_word(&token); break;
  case '[': EMIT(LBRACKET);
  case '\\': EMIT(BACKSLASH);
  case ']': EMIT(RBRACKET);
  case '^': EMIT(CARET);
  case '_': EMIT(UNDERSCORE);
  case '`': EMIT(BACK_QUOTE);
  case 'a':
  case 'b':
  case 'c':
  case 'd':
  case 'e':
  case 'f':
  case 'g':
  case 'h':
  case 'i':
  case 'j':
  case 'k':
  case 'l':
  case 'm':
  case 'n':
  case 'o':
  case 'p':
  case 'q':
  case 'r':
  case 's':
  case 't':
  case 'u':
  case 'v':
  case 'w':
  case 'x':
  case 'y':
  case 'z': fetch_word(&token); break;
  case '{': EMIT(LBRACE);
  case '|': EMIT(PIPE);
  case '}': EMIT(RBRACE);
  case '~': EMIT(TILDE);
  default: throw 4;
  }
  */
  
  switch (fetched_byte) {
  case '(': EMIT(LPAREN);
  case ')': EMIT(RPAREN)
    /*
  case 'A': 
  case 'B':
  case 'C':
  case 'D':
  case 'E':
  case 'F':
  case 'G':
  case 'H':
  case 'I':
  case 'J':
  case 'K':
  case 'L':
  case 'M':
  case 'N':
  case 'O':
  case 'P':
  case 'Q':
  case 'R':
  case 'S':
  case 'T':
  case 'U':
  case 'V':
  case 'W':
  case 'X':
  case 'Y':
  case 'Z':
    */
  case 'A' ... 'Z':
  case 'a' ... 'z': fetch_word(&token); break;
    /*
  case 'a':
  case 'b':
  case 'c':
  case 'd':
  case 'e':
  case 'f':
  case 'g':
  case 'h':
  case 'i':
  case 'j':
  case 'k':
  case 'l':
  case 'm':
  case 'n':
  case 'o':
  case 'p':
  case 'q':
  case 'r':
  case 's':
  case 't':
  case 'u':
  case 'v':
  case 'w':
  case 'x':
  case 'y':
  case 'z': fetch_word(&token); break;
    */
  default:  
    if (is_digit(fetched_byte)) {
      fetch_num(&token);
    } else {
      fetch_op(&token);
    }
  }

  return token;
}
