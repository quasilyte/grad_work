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
  Type ty;

  for (ast::Node* operand : op->operands) {
    ty = TypeDeducer::Run(operand);

    if (ty.IsArith()) {
      if (ty.IsReal()) {
        return ty;
      }
    } else {
      throw "invalid operand type in arith expression";
    }
  }

  return ty.IsInt() || ty.IsUnknown() ? Type::Int() : Type::Num();
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

// #FIXME: those can be refactored in 1 visit of base BoolOp node,
// but perfomance should be tested.
void TypeDeducer::Visit(ast::Lt*) {
  result = Type::Int();
}

void TypeDeducer::Visit(ast::Gt*) {
  result = Type::Int();
}

void TypeDeducer::Visit(ast::SetVar*) {
  throw "set! is not an expression";
}

void TypeDeducer::Visit(ast::SetAttr*) {
  throw "set! is not an expression";
}

void TypeDeducer::Visit(ast::DefVar*) {
  throw "def is not an expression";
}

void TypeDeducer::Visit(ast::If* node) {
  auto ty1 = TypeDeducer::Run(node->on_true);
  auto ty2 = TypeDeducer::Run(node->on_false);

  // #FIXME: maybe this "Unknown" handling should be moved to ExtendedWith()
  if (ty1.IsUnknown()) {
    result = ty2;
  } else if (ty2.IsUnknown()) {
    result = ty1;
  } else {
    result = ty1.ExtendedWith(ty2);
  }
}

void TypeDeducer::Visit(ast::Var* node) {
  result = node->type;
}

void TypeDeducer::Visit(ast::LambdaExpr* node) {
  result = Type{node->id};
}

void TypeDeducer::Visit(ast::FuncCall* node) {
  result = node->func->ret_type;
}

void TypeDeducer::Visit(ast::VarCall* node) {
  result = node->func->ret_type;
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
