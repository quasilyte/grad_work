#pragma once

#include "dt/str_view.hpp"

namespace sym {
  const i32 MAX_UNIQ_SUFFIXES = 2015;

  dt::StrView gen_suffix(u32 idx);
  const char* mangle(char);
}
