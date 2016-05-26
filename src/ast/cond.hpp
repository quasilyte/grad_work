#pragma once

#include "ast/node.hpp"
#include "ast/atoms.hpp"

namespace ast {
  struct If;
  struct IntCase;
}

struct ast::If: public Node {
public:
  If(Node* cond, Node* on_true, Node* on_false);

  void Accept(Visitor*);

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

