#include "cc/type_deducer.hpp"

#include "ast/node.hpp"
#include "ast/builtins.hpp"
#include "ast/cond.hpp"
#include "ast/atoms.hpp"
#include "sym/fn.hpp"
#include "intrinsic/type_ops.hpp"

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

sym::Type deduce_arith_type(ast::Operation* op) {
  Type result_type = TypeDeducer::Run(op->operands[0]);
  if (!result_type.IsArith()) {
    throw "invalid operand type in arith expression";
  }

  for (uint i = 1; i < op->operands.size(); ++i) {
    auto type = TypeDeducer::Run(op->operands[i]);
    if (!result_type.SameAs(type)) {
      if (type.IsArith()) {
        throw "mixed arith types";
      } else if (!type.IsUnknown()) {
        throw "invalid operand type in arith expression";
      }
    }
  }

  return result_type;
}

void TypeDeducer::Visit(ast::Sum* sum) {
  result = deduce_arith_type(sum);
}

void TypeDeducer::Visit(ast::Mul* mul) {
  result = deduce_arith_type(mul);
}

void TypeDeducer::Visit(ast::Sub* sub) {
  result = deduce_arith_type(sub);
}

void TypeDeducer::Visit(ast::Lt*) {
  result = Type::Int();
}

void TypeDeducer::Visit(ast::Gt*) {
  result = Type::Int();
}

void TypeDeducer::Visit(ast::SetVar*) {
  result = Type::Void();
}

void TypeDeducer::Visit(ast::SetAttr*) {
  result = Type::Void();
}

void TypeDeducer::Visit(ast::DefVar*) {
  result = Type::Void();
}

void TypeDeducer::Visit(ast::If* node) {
  // Both `on_true` & `on_false` already coerced to the same
  // types, so we can peek any of them.
  result = TypeDeducer::Run(node->on_true);
}

void TypeDeducer::Visit(ast::IntCase* node) {
  result = node->ret_type;
}

void TypeDeducer::Visit(ast::Var* node) {
  result = node->type;
}

void TypeDeducer::Visit(ast::LambdaExpr* node) {
  result = node->type;
}

void TypeDeducer::Visit(ast::FuncCall* node) {
  result = node->func->ret_type;
}

void TypeDeducer::Visit(ast::VarCall* node) {
  result = node->func->ret_type;
}

void TypeDeducer::Visit(ast::DynamicCall*) {
  result = Type::Any();
}

void TypeDeducer::Visit(ast::CompoundLiteral* node) {
  result = node->type;
}

void TypeDeducer::Visit(ast::AttrAccess* node) {
  result = node->attr->type;
}

void TypeDeducer::Visit(ast::Intrinsic* node) {
  result = node->type;
}

void TypeDeducer::Visit(ast::IntrinsicCall1* node) {
  result = intrinsic::ret_type_of(node->type);
}

void TypeDeducer::Visit(ast::Each*) {
  result = Type::Void();
}
