#pragma once

#include <sym/type.hpp>
#include <dt/str_view.hpp>

namespace go_cc {
  sym::Type get_module_symbol(dt::StrView name);
}
