#pragma once

#include "ast/node.hpp"

namespace ast {
  struct If;
}

struct ast::If: public Node {
public:
  If(Node* cond, Node* on_true, Node* on_false);

  void Accept(Visitor*);

  Node* cond;
  Node* on_true;
  Node* on_false;
};

