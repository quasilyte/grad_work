#pragma once

#include "typedefs.hpp"
#include "dt/str_view.hpp"

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

  enum Tag Tag() const noexcept;
  u32 Len() const noexcept;
  const char* Val() const noexcept;

  dt::StrView AsStrView() const noexcept;

  bool IsAtom() const noexcept;
  bool IsInt() const noexcept;
  bool IsReal() const noexcept;
  bool IsStr() const noexcept;
  bool IsWord() const noexcept;
  bool IsList() const noexcept;
  bool IsEof() const noexcept;

private:
  enum Tag tag;
  u32 len;
  const char* val;

  friend class TokenStream;
};

static_assert(
  sizeof(lex::Token) == 16 || sizeof(lex::Token) == 12,
  "type size expectations failed"
);
