#pragma once

#include <typedefs.hpp>

namespace go_cc {
  struct Expr;
}

struct go_cc::Expr {
  enum: u32 {
    FN_CALL,
    GROUP,
    INT,
    REAL,
    STR,
  };

  u32 tag;
  u32 len;
  const char* val;
};
