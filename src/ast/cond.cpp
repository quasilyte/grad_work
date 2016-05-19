#include "ast/cond.hpp"

#include "ast/visitor.hpp"

using namespace ast;

If::If(Node *cond, Node *on_true, Node *on_false):
cond{cond}, on_true{on_true}, on_false{on_false} {}

void If::Accept(Visitor* v) { v->Visit(this); }
