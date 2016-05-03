#include "token_stream.hpp"

#include "char_type.hpp"

using namespace lex;

/**
 * public:
 */

void TokenStream::next() noexcept {
  token.value += token.len;
  consume_spaces();

  if (token.value == end) {
    token.tag = SOURCE_END;
  } else {
    eval();
  }
}

const Token& TokenStream::next_token() noexcept {
  next();
  return token;
}

Tag TokenStream::next_tag() noexcept {
  next();
  return token.tag;
}

const Token& TokenStream::current() const noexcept {
  return token;
}

Tag TokenStream::current_tag() const noexcept {
  return token.tag;
}

/**
 * private:
 */

void TokenStream::eval() noexcept {
  token.len = 1;
    
  switch (*token.value) {
  case 0:
  case 1:
  case 2:
  case 3:
  case 4:      
  case 5:
  case 6:
  case 7:
  case 8:
  case 9:	  
  case 10:
  case 11:
  case 12:
  case 13:
  case 14:	
  case 15:
  case 16:
  case 17:
  case 18:
  case 19:	
  case 20:
  case 21:
  case 22:
  case 23:
  case 24:	
  case 25:
  case 26:
  case 27:
  case 28:
  case 29:	
  case 30:
  case 31:
  case 32: throw NonPrintableCharError{};
  case '!': token.tag = BANG; break;
  case '"': eval_str(); break;
  case '#': token.tag = HASH; break;
  case '$': token.tag = DOLLAR; break;
  case '%': token.tag = PERCENT; break;
  case '&': eval_op(); break;
  case '\'': token.tag = QUOTE; break;
  case '(': token.tag = LPAREN; break;
  case ')': token.tag = RPAREN; break;
  case '*': eval_op(); break;
  case '+': eval_op(); break;
  case ',': token.tag = COMMA; break;
  case '-': eval_op(); break;
  case '.': token.tag = DOT; break;
  case '/': eval_op(); break;
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
  case ':': token.tag = COLON; break;
  case ';': token.tag = SEMICOLON; break;
  case '<': token.tag = LT; break;
  case '=': eval_op(); break;
  case '>': token.tag = GT; break;
  case '?': token.tag = QUES; break;
  case '@': token.tag = AT; break;
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
  case 'Z': eval_word(); break;
  case '[': token.tag = LBRACKET; break;
  case '\\': token.tag = BACKSLASH; break;
  case ']': token.tag = RBRACKET; break;
  case '^': token.tag = CARET; break;
  case '_': token.tag = UNDERSCORE; break;
  case '`': token.tag = BACK_QUOTE; break;
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
  case 'z': eval_word(); break;
  case '{': token.tag = LBRACE; break;
  case '|': token.tag = PIPE; break;
  case '}': token.tag = RBRACE; break;
  case '~': token.tag = TILDE; break;
  default: throw NonPrintableCharError{};
  }
}

void TokenStream::eval_word() noexcept {
  // We enter this loop after passing first alpha char,
  // so no need to handle it. We iterate over \w char class
  while (is_word(current_char())) {
    token.len += 1;
  }

  token.tag = WORD;
}

void TokenStream::eval_str() noexcept {
  while ('"' != current_char()) {
    token.len += 1;
  }

  token.len += 1; // Pass over closing '"'
  token.tag = STR;
}

void TokenStream::eval_number() noexcept {
  collect_digits();

  if ('.' == current_char()) {
    token.len += 1; // Pass over dot
    collect_digits();
    token.tag = REAL;
  } else {
    token.tag = INTEGER;
  }
}

void TokenStream::eval_op() noexcept {
  u32 hash = *token.value;
  for (token.len = 1; not_space(current_char()); ++token.len) {
    hash = m_hash::encode1(hash, current_char());
  }
  token.tag = static_cast<Tag>(hash);
}

void TokenStream::collect_digits() noexcept {
  while (is_digit(current_char())) {
    token.len += 1;
  }
}

void TokenStream::consume_spaces() noexcept {
  while (is_space(*token.value)) {
    ++token.value;
  }
}

char TokenStream::current_char() const noexcept {
  return token.value[token.len];
}
