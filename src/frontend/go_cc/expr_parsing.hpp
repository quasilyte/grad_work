#pragma once

#include "dt/str_view.hpp"

namespace ast {
  struct Node;
}

namespace lex {
  struct Cursor;
}

namespace go_cc {
  ast::Node* parse_expr(lex::Cursor*, const char* terms);
  ast::Node* parse_expr(dt::StrView expr, const char* terms);
}
