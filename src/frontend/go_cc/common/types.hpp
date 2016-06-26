#pragma once

#include <sym/type.hpp>

namespace dt {
  class StrView;
}

namespace go_cc {
  sym::Type type_by_name(const dt::StrView&);
  const char* name_by_type(sym::Type);
}
