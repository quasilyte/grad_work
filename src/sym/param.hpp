#pragma once

#include "dt/str_view.hpp"
#include "sym/type.hpp"

namespace sym {
  struct Param;
}

struct sym::Param {
  Param(dt::StrView name, Type type);

  dt::StrView name;
  Type type;
};
