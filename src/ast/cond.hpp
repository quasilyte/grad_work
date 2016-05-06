#pragma once

#include "ast/node.hpp"

namespace ast {
  struct If;
}

struct ast::If: public Node {
  If(Node* cond, Node* on_true, Node* on_false);
  void generate_code(io::FileWriter*);
  const char* get_type_name() const;
  Node* cond;
  Node* on_true;
  Node* on_false;
};
