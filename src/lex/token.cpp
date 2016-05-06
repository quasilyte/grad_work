#include "lex/token.hpp"

#include <cstring>

using namespace lex;

Token::Token(Tag tag, const char* val):
tag{tag}, len{static_cast<u32>(std::strlen(val))}, val{val} {}

Token::Token(Tag tag, const char* val, u32 len):
tag{tag}, len{len}, val{val} {}

Token::Tag Token::get_tag() const noexcept {
  return tag;
}

u32 Token::get_len() const noexcept {
  return len;
}

const char* Token::get_val() const noexcept {
  return val;
}

bool Token::is_atom() const noexcept {
  return tag > BEGIN_ATOM && tag < END_ATOM;
}

bool Token::is_int() const noexcept {
  return tag == INT;
}

bool Token::is_real() const noexcept {
  return tag == REAL;
}

bool Token::is_str() const noexcept {
  return tag == STR;
}

bool Token::is_word() const noexcept {
  return tag == WORD;
}

bool Token::is_list() const noexcept {
  return tag == LIST;
}

bool Token::is_eof() const noexcept {
  return tag == SOURCE_END;
}
