#include "ast/literals.hpp"

#include "sym/sym.hpp"
#include "ast/visitor.hpp"

using namespace ast;

Atom::Atom(dt::StrView datum): datum{datum} {}

#define GEN_ATOM(NAME) \
  void NAME::Accept(Visitor* v) { v->Visit(this); } \
  sym::Type NAME::Type() { return sym::Type::NAME(); }

GEN_ATOM(Int)
GEN_ATOM(Real)
GEN_ATOM(Str)

CompoundLit::CompoundLit(ast::NodeList&& initializers, sym::Type type):
initializers{initializers}, type{type} {}
void CompoundLit::Accept(Visitor* v) { v->Visit(this); }

sym::Type CompoundLit::Type() {
  return type;
}
