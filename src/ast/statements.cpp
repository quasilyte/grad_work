#include "ast/statements.hpp"

#include "ast/visitor.hpp"

using namespace ast;

Return::Return(Node *val): val{val} {}
void Return::Accept(Visitor* v) { v->Visit(this); }
sym::Type Return::Type() { return val->Type(); }
