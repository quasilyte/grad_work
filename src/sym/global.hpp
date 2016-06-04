#pragma once

#include "dt/str_view.hpp"
#include "sym/type.hpp"
#include "ast/node.hpp"

namespace sym {
  struct Global;
}

struct sym::Global {
  dt::StrView name;
  ast::Node* val;
  sym::Type type;
};
