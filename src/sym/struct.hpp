#pragma once

#include <vector>
#include "dt/str_view.hpp"
#include "sym/param.hpp"

namespace sym {
  struct Struct;
}

struct sym::Struct {
  dt::StrView name;
  std::vector<sym::Param> attrs;
};
