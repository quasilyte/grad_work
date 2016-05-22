#pragma once

#include "sym/param.hpp"
#include "dt/str_view.hpp"
#include "sym/struct.hpp"
#include <vector>

namespace unit {
  void def_struct(dt::StrView name, sym::Struct::AttrList&&);
  sym::Struct* get_struct(dt::StrView name);
  sym::Struct* get_struct(sym::Type);
  sym::Struct* get_struct(uint idx);
  uint struct_count();
}
