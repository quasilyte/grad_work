#pragma once

#include <vector>
#include "dt/str_view.hpp"
#include "sym/param.hpp"
#include "sym/type.hpp"

namespace sym {
  struct Struct;
}

struct sym::Struct {
  dt::StrView name;
  std::vector<sym::Param> attrs;
  sym::Type type;

  Struct(dt::StrView, std::vector<sym::Param>&&, sym::Type);

  sym::Param* Attr(dt::StrView name);
};
