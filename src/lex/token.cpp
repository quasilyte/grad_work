#include "token.hpp"

#include <cstring>
#include "parse_val.hpp"

using namespace lex;

Token::Token(Tag tag, const char *value, usize len):
value{value}, tag{tag}, len{len} {}

Token::Token(Tag tag, const char *value):
value{value}, tag{tag}, len{strlen(value)} {}

real Token::fetch_real() const {
  return parse_real(value);
}

integer Token::fetch_integer() const {
  return parse_integer(value);
}

u64 Token::hash_value() const {
  if (len > MAX_HASHABLE_LEN) {
    return NIL_HASH;
  }

  return m_hash::encode9(value, len);
}
