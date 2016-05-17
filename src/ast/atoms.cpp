#include "ast/atoms.hpp"

#include "sym/sym.hpp"
#include "ast/visitor.hpp"

using namespace ast;
using namespace sym;

Atom::Atom(dt::StrView datum): datum{datum} {}

void Int::Accept(Visitor* v) { v->Visit(this); }
void Real::Accept(Visitor* v) { v->Visit(this); }
void Str::Accept(Visitor* v) { v->Visit(this); }
void Sym::Accept(Visitor* v) { v->Visit(this); }

Var::Var(dt::StrView name, const Type* type):
name{name}, type{type} {}

void Var::Accept(Visitor* v) { v->Visit(this); }

CompoundLiteral::CompoundLiteral(std::vector<Node *>&& initializers, Type ty):
initializers{initializers}, type{ty} {}

void CompoundLiteral::Accept(Visitor* v) { v->Visit(this); }
