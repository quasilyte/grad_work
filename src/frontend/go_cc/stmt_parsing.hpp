#pragma once

#include "dt/str_view.hpp"

namespace ast {
  struct Node;
}

namespace lex {
  struct Cursor;
}

namespace go_cc {
  ast::Node* parse_return(lex::Cursor*);
  ast::Node* parse_short_var_decl(dt::StrView id, lex::Cursor*);
  ast::Node* parse_plus_assignment(dt::StrView id, lex::Cursor*);
  ast::Node* parse_if(lex::Cursor*);
}
