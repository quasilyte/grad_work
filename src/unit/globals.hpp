#pragma once

#include <dt/str_view.hpp>
#include <sym/global.hpp>

namespace unit {
  void def_global(dt::StrView name, ast::Node* val, sym::Type);
  sym::Global* get_global(dt::StrView name);
  sym::Global* get_global(uint idx);
  uint global_count();
}
