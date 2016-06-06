#pragma once

#include <ast/node.hpp>
#include <ast/literals.hpp>

namespace ast {
  struct IfStmt;
  struct IfExpr;
  struct IntCase;
}

struct ast::IfStmt: Node {
  IfStmt(Node* cond, std::vector<Node*>&& on_true, std::vector<Node*>&& on_false);

  void Accept(Visitor*) override;
  sym::Type Type() override;

  Node* cond;
  std::vector<Node*> on_true;
  std::vector<Node*> on_false;
};

struct ast::IfExpr: Node {
  IfExpr(Node* cond, Node* on_true, Node* on_false);

  void Accept(Visitor*) override;
  sym::Type Type() override;

  Node* cond;
  Node* on_true;
  Node* on_false;
};

struct ast::IntCase: public Node {
  struct Clause {
    dt::StrView cond;
    Node* expr;
  };

  typedef std::vector<Clause> ClauseList;

  // IntCase(Node* cond_expr, ClauseList&&, Node* default_expr);
  IntCase(Node* cond_expr, ClauseList&&, sym::Type ret_type);

  void Accept(Visitor*);

  Node* cond_expr;
  ClauseList clauses;
  sym::Type ret_type;
  // Node* default_expr;
};

