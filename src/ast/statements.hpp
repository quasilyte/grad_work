#pragma once

#include <ast/node.hpp>

namespace ast {
  struct Return;
}

struct ast::Return: public Node {
  Return(Node* val);

  void Accept(Visitor*) override;
  sym::Type Type() override;

  Node* val;
};
