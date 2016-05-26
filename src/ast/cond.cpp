#include "ast/cond.hpp"

#include "ast/visitor.hpp"

using namespace ast;

If::If(Node *cond, Node *on_true, Node *on_false):
cond{cond}, on_true{on_true}, on_false{on_false} {}

void If::Accept(Visitor* v) { v->Visit(this); }

/*
IntCase::IntCase(Node* cond_expr, ClauseList&& clauses, Node* default_expr):
cond_expr{cond_expr}, clauses{clauses}, default_expr{default_expr} {}
*/

IntCase::IntCase(Node* cond_expr, ClauseList&& clauses, sym::Type ret_type):
cond_expr{cond_expr}, clauses{clauses}, ret_type{ret_type} {}

void IntCase::Accept(Visitor* v) { v->Visit(this); }
