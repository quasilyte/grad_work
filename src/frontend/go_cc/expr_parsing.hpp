#pragma once

#include <dt/str_view.hpp>

namespace ast {
  struct Node;
}

namespace go_cc {
  class Reader;

  // ast::Node* parse_expr(Reader*, const char* terms);
  ast::Node* parse_expr(dt::StrView);
}
