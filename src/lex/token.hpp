#pragma once

#include "typedefs.hpp"

namespace lex {
  class Token;
  class TokenStream;
}

class lex::Token {
public:
  enum Tag: i32 {
    BEGIN_ATOM,
    INT,
    REAL,
    STR,
    END_ATOM,
    WORD,
    LIST,
    SOURCE_END,
  };

  Token(Tag, const char* val);
  Token(Tag, const char* val, u32 len);

  Tag get_tag() const noexcept;
  u32 get_len() const noexcept;
  const char* get_val() const noexcept;

  bool is_atom() const noexcept;
  bool is_int() const noexcept;
  bool is_real() const noexcept;
  bool is_str() const noexcept;
  bool is_word() const noexcept;
  bool is_list() const noexcept;
  bool is_eof() const noexcept;

private:
  Tag tag;
  u32 len;
  const char* val;

  friend class TokenStream;
};

static_assert(
  sizeof(lex::Token) == 16 || sizeof(lex::Token) == 12,
  "type size expectations failed"
);
