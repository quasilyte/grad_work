#pragma once

#include <sym/type.hpp>

namespace intrinsic {
  sym::Type ret_type_of(sym::Type f);
  uint arity_of(sym::Type f);
  sym::Type param_of(sym::Type, uint idx);
  sym::Type cast(sym::Type from, sym::Type to);
}
