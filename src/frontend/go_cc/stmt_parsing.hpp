#pragma once

#include <dt/str_view.hpp>

namespace ast {
  struct Node;
}

namespace go_cc {
  class Reader;

  ast::Node* parse_assignment(dt::StrView name, Reader*);
  ast::Node* parse_return(Reader*);
  ast::Node* parse_short_var_decl(dt::StrView id, Reader*);
  ast::Node* parse_plus_assignment(dt::StrView id, Reader*);
  ast::Node* parse_if(Reader*);
}
