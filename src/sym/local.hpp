#pragma once

#include "dt/str_view.hpp"

namespace sym {
  class Type;
  struct Local;
}

struct sym::Local {
  const dt::StrView* bound_name;
  const sym::Type* type;
};

