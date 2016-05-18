#include "cc/type_deducer.hpp"

#include "ast/node.hpp"
#include "ast/builtins.hpp"
#include "ast/cond.hpp"
#include "ast/atoms.hpp"

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

void TypeDeducer::Visit(ast::Sym*) {
  result = Type::Sym();
}

void TypeDeducer::Visit(ast::Sum* sum) {
  for (ast::Node* operand : sum->operands) {
    result = TypeDeducer::Run(operand);
    if (result.IsArith()) {
      if (result.IsReal()) {
        return;
      }
    } else {
      throw "not arith in sum";
    }
  }

  if (!result.IsInt()) {
    result = Type::Num();
  }
}

void TypeDeducer::Visit(ast::SetVar*) {
  throw "set! is not an expression";
}

void TypeDeducer::Visit(ast::DefVar*) {
  throw "def is not an expression";
}

void TypeDeducer::Visit(ast::If* node) {
  auto ty1 = TypeDeducer::Run(node->on_true);
  auto ty2 = TypeDeducer::Run(node->on_false);

  result = ty1.ExtendedWith(ty2);
}

void TypeDeducer::Visit(ast::Var* node) {
  result = *node->type;
}

void TypeDeducer::Visit(ast::FuncCall* node) {
  result = node->ty;
}

void TypeDeducer::Visit(ast::CompoundLiteral* node) {
  result = node->type;
}

void TypeDeducer::Visit(ast::AttrAccess* node) {
  result = node->attr->type;
}
