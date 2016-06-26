#pragma once

#include <sym/type.hpp>
#include <dt/str_view.hpp>

namespace cc {
  void strict_type_check(dt::StrView name, sym::Type a, sym::Type b);
}
