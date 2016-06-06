#pragma once

#include <dt/str_view.hpp>
#include <sym/type.hpp>

namespace sym {
  struct Param;
}

struct sym::Param {
  dt::StrView name;
  sym::Type type;
};
