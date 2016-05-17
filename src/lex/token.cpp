#include "lex/token.hpp"

#include <cstring>

using namespace lex;

Token::Token(enum Tag tag, const char* val):
tag{tag}, len{static_cast<u32>(std::strlen(val))}, val{val} {}

Token::Token(enum Tag tag, const char* val, u32 len):
tag{tag}, len{len}, val{val} {}

enum Token::Tag Token::Tag() const noexcept {
  return tag;
}

const char* Token::Data() const noexcept {
  return val;
}

u32 Token::Len() const noexcept {
  return len;
}

bool Token::IsAtom() const noexcept {
  return tag > BEGIN_ATOM && tag < END_ATOM;
}

bool Token::IsInt() const noexcept {
  return tag == INT;
}

bool Token::IsReal() const noexcept {
  return tag == REAL;
}

bool Token::IsStr() const noexcept {
  return tag == STR;
}

bool Token::IsWord() const noexcept {
  return tag == WORD;
}

bool Token::IsList() const noexcept {
  return tag == LIST;
}

bool Token::IsEof() const noexcept {
  return tag == SOURCE_END;
}

bool Token::Is(enum Tag tag) const noexcept {
  return this->tag == tag;
}

