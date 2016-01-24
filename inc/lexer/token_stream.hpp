#pragma once

#include "typedefs.hpp"

#define SET_TAG(TAG) token.tag = TAG; break;
#define TAG_CASE(CHAR, TAG) case CHAR: SET_TAG(TAG);
#define EVAL(FN) eval_##FN(); break;

class TokenStream {
public:
  TokenStream(const char *input): token{input, 0, SOURCE_END} {}

  void next() {
    token.value += token.len;
    consume_spaces();
    eval();
  }
  
  Token* next_token() {
    next();
    return &token;
  }

  TokenTag next_tag() {
    next();
    return token.tag;
  }

  Token* current() noexcept {
    return &token;
  }
  
  void eval() {
    token.len = 1;
    
    switch (*token.value) {
    TAG_CASE('\0', SOURCE_END);
    NONPRINTABLE_CASE: throw "nonprintable char met";
    TAG_CASE('!', BANG);
    case '"': throw "cant handle string literals yet";
    TAG_CASE('#', HASH);
    TAG_CASE('$', DOLLAR);
    TAG_CASE('%', PERCENT);
    case '&': EVAL(op);
    TAG_CASE('\'', QUOTE);
    TAG_CASE('(', LPAREN);
    TAG_CASE(')', RPAREN);
    case '*': EVAL(op);
    case '+': EVAL(op);
    TAG_CASE(',', COMMA);
    case '-': EVAL(op);
    TAG_CASE('.', DOT);
    case '/': EVAL(op);
    DIGIT_CASE: EVAL(number);
    TAG_CASE(':', COLON);
    TAG_CASE(';', SEMICOLON);
    TAG_CASE('<', LT);
    case '=': EVAL(op);
    TAG_CASE('>', GT);
    TAG_CASE('?', QUES);
    TAG_CASE('@', AT);
    UCASE_CASE: EVAL(word);
    TAG_CASE('[', LBRACKET);
    TAG_CASE('\\', BACKSLASH);
    TAG_CASE(']', RBRACKET);
    TAG_CASE('^', CARET);
    TAG_CASE('_', UNDERSCORE); // Yeah, no leading underscore for identifiers
    TAG_CASE('`', BACK_QUOTE);
    LCASE_CASE: EVAL(word);
    TAG_CASE('{', LBRACE);
    TAG_CASE('|', PIPE);
    TAG_CASE('}', RBRACE);
    TAG_CASE('~', TILDE);
    default:
      throw "nonprintable char met";
    }
  }
  
private:
  Token token;

  void eval_word() {
    // We enter this loop after passing first alpha char,
    // so no need to handle it. We iterate over \w char class
    while (is_word(current_char())) {
      ++token.len;
    }

    token.tag = WORD;
  }

  void collect_digits() {
    while (is_digit(current_char())) {
      ++token.len;
    }
  }

  void eval_number() {
    collect_digits();

    if ('.' == current_char()) {
      ++token.len; // Pass over dot
      collect_digits();
      token.tag = REAL;
    } else {
      token.tag = DECIMAL;
    }
  }

  void eval_op() {
    unsigned hash = *token.value;
    for (token.len = 1; not_space(current_char()); ++token.len) {
      hash <<= 7;
      hash += current_char();
    }
    token.tag = static_cast<TokenTag>(hash);
  }
  
  void consume_spaces() {
    while (is_space(*token.value)) {
      ++token.value;
    }
  }

  char current_char() const {
    return token.value[token.len];
  }
};
	     
#undef SET_TAG
#undef TAG_CASE
#undef EVAL
