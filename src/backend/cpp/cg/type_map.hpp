#pragma once

#include "sym/type.hpp"

namespace dt {
  class StrView;
}

namespace cpp_cg {
  dt::StrView& type_name(sym::Type);
}
