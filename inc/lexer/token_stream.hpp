#pragma once

#include "typedefs.hpp"
#include "m_hash.hpp"

#define SET_TAG(TAG) token.tag = TAG; break;
#define TAG_CASE(CHAR, TAG) case CHAR: SET_TAG(TAG);
#define EVAL(FN) eval_##FN(); break;

class TokenStream {
public:
  TokenStream(const char *input, size_t len):
    token{SOURCE_END, input, 0},
    end{input + len}
  {}

  TokenStream(Token *tok):
    token{SOURCE_END, tok->value, 0},
    end{tok->value + tok->len - 1}
  {}

  void next() {
    token.value += token.len;
    consume_spaces();

    if (token.value == end) {
      token.tag = SOURCE_END;
    } else {
      eval();
    }
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
    NONPRINTABLE_CASE: throw "nonprintable char met";
    TAG_CASE('!', BANG);
    case '"': EVAL(str);
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
  const char *const end;

  void eval_word() {
    // We enter this loop after passing first alpha char,
    // so no need to handle it. We iterate over \w char class
    while (is_word(current_char())) {
      ++token.len;
    }

    token.tag = WORD;
  }

  void eval_str() {
    while ('"' != current_char()) {
      token.len += 1;
    }

    token.len += 1; // Pass over closing "
    token.tag = STR;
  }

  void collect_digits() {
    while (is_digit(current_char())) {
      token.len += 1;
    }
  }

  void eval_number() {
    collect_digits();

    if ('.' == current_char()) {
      token.len += 1; // Pass over dot
      collect_digits();
      token.tag = REAL;
    } else {
      token.tag = DECIMAL;
    }
  }

  void eval_op() {
    u32 hash = *token.value;
    for (token.len = 1; not_space(current_char()); ++token.len) {
      hash = m_encode(hash, current_char());
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
