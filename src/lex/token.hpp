#pragma once

#include <typedefs.hpp>
#include <dt/str_view.hpp>

namespace lex {
  struct Token;
}

struct lex::Token {
  const char* data;
  u32 len;
  u32 tag;
};

static_assert(
  sizeof(lex::Token) == 16 || sizeof(lex::Token) == 12,
  "type size expectations failed"
);
