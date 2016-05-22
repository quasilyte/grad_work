#pragma once

#include "dt/str_view.hpp"
#include "sym/type.hpp"

namespace unit {
  void def_global(dt::StrView name, sym::Type);
  sym::Type get_global(dt::StrView name);
}
