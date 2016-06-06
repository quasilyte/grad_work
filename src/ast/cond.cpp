#include <ast/cond.hpp>

#include <ast/visitor.hpp>

using namespace ast;

IfStmt::IfStmt(Node* cond, std::vector<Node*>&& on_true, std::vector<Node*>&& on_false):
cond{cond}, on_true{on_true}, on_false{on_false} {}

void IfStmt::Accept(Visitor* v) { v->Visit(this); }

sym::Type IfStmt::Type() {
  return sym::Type::Void();
}

IfExpr::IfExpr(Node* cond, Node* on_true, Node* on_false):
cond{cond}, on_true{on_true}, on_false{on_false} {}

void IfExpr::Accept(Visitor* v) { v->Visit(this); }

sym::Type IfExpr::Type() {
  return on_true->Type().ExtendedWith(on_false->Type());
}

/*
IntCase::IntCase(Node* cond_expr, ClauseList&& clauses, Node* default_expr):
cond_expr{cond_expr}, clauses{clauses}, default_expr{default_expr} {}
*/

IntCase::IntCase(Node* cond_expr, ClauseList&& clauses, sym::Type ret_type):
cond_expr{cond_expr}, clauses{clauses}, ret_type{ret_type} {}

void IntCase::Accept(Visitor* v) { v->Visit(this); }
