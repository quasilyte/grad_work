#pragma once

#include "typedefs.hpp"

namespace ast {
  struct GlobalVar;
}

struct ast::GlobalVar {
  const char* name;
  u32 name_len;
};

static_assert(
  sizeof(ast::GlobalVar) == 16 || sizeof(ast::GlobalVar) == 8,
  "type size expectations failed"
);
