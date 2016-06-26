#pragma once

#include <ast/node.hpp>
#include <dt/str_view.hpp>

namespace ast {
  struct Return;
  struct Assign;
  struct SumAssign;
}

struct ast::Return: Node {
  Return(Node* val);

  void Accept(Visitor*) override;
  sym::Type Type() override;

  Node* val;
};

struct ast::Assign: Node {
  Assign(dt::StrView recv_name, Node* expr);

  void Accept(Visitor*) override;
  sym::Type Type() override;

  dt::StrView recv_name;
  Node* expr;
};

struct ast::SumAssign: Assign {
  using Assign::Assign;

  void Accept(Visitor*) override;
};
