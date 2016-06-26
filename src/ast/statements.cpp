#include <ast/statements.hpp>

#include <ast/visitor.hpp>

using namespace ast;

Return::Return(Node *val): val{val} {}
void Return::Accept(Visitor* v) { v->Visit(this); }
sym::Type Return::Type() { return val->Type(); }

Assign::Assign(dt::StrView recv_name, Node* expr):
recv_name{recv_name}, expr{expr} {}
void Assign::Accept(Visitor* v) { v->Visit(this); }
sym::Type Assign::Type() { return sym::Type::Void(); }

void SumAssign::Accept(Visitor* v) { v->Visit(this); }
