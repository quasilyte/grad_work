#pragma once

#include <dt/str_view.hpp>
#include <sym/type.hpp>

namespace ast {
  struct Node;
}

namespace unit {
  void create_scope_level();
  void drop_scope_level();

  void scope_push(dt::StrView name, sym::Type type);
  sym::Type scope_symbol(dt::StrView name);
  sym::Type scope_local_symbol(dt::StrView name);
}
