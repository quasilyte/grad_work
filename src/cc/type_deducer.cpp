#include "cc/type_deducer.hpp"

#include "ast/node.hpp"
#include "ast/builtins.hpp"
#include "ast/cond.hpp"

using namespace cc;
using namespace sym;

Type TypeDeducer::Run(ast::Node* root) {
  TypeDeducer self;
  self.Visit(root);

  return self.result;
}

void TypeDeducer::Visit(ast::Node* root) {
  root->Accept(this);
}

void TypeDeducer::Visit(ast::Int*) {
  result = Type::Int();
}

void TypeDeducer::Visit(ast::Real*) {
  result = Type::Real();
}

void TypeDeducer::Visit(ast::Str*) {
  result = Type::Str();
}

void TypeDeducer::Visit(ast::Sum* sum) {
  for (ast::Node* operand : sum->Operands()) {
    operand->Accept(this);
    if (result.IsReal()) {
      break;
    }
  }
}

void TypeDeducer::Visit(ast::SetGlobal*) {
  throw "set! is not an expression";
}

void TypeDeducer::Visit(ast::DefLocal*) {
  throw "def is not an expression";
}

void TypeDeducer::Visit(ast::If* node) {
  node->on_true->Accept(this);
  auto ty1 = result;
  node->on_false->Accept(this);
  auto ty2 = result;

  result = ty1.ExtendedWith(ty2);
}
