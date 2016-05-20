#pragma once

#include "dt/str_view.hpp"

namespace sym {
  dt::StrView gen_suffix(u32 idx);
  const char* mangle(char);
}
