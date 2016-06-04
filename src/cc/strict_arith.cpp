#include "cc/strict_arith.hpp"

#include "ast/builtins.hpp"
#include "ast/cond.hpp"
#include "errors.hpp"

using namespace cc;
using namespace ast;

ast::Node* num_type_checked(ast::BinaryOp* node) {
  auto lhs_type = node->operands.lhs->Type();
  auto rhs_type = node->operands.rhs->Type();

  if (!lhs_type.IsArith()) {
    throw err::InvalidTypeInArith{lhs_type, node->Symbol()};
  }

  if (lhs_type.SameAs(rhs_type)) {
    return node;
  } else {
    throw err::MixedArithTypes{lhs_type, rhs_type, node->Symbol()};
  }
}

ast::Node* cc::strict_sum(ast::BinaryNode operands) {
  return num_type_checked(new ast::Sum{operands, operands.lhs->Type()});
}

ast::Node* cc::strict_sub(ast::BinaryNode operands) {
  return num_type_checked(new ast::Sub{operands, operands.lhs->Type()});
}

ast::Node* cc::strict_mul(ast::BinaryNode operands) {
  return num_type_checked(new ast::Mul{operands, operands.lhs->Type()});
}

ast::Node* cc::strict_div(ast::BinaryNode operands) {
  return num_type_checked(new ast::Div{operands, operands.lhs->Type()});
}

Node* cc::strict_eq(BinaryNode operands) {
  return num_type_checked(new ast::NumEq{operands});
}

Node* cc::strict_if_stmt(Node* cond, NodeList&& on_true, NodeList&& on_false) {
  auto cond_type = cond->Type();

  if (cond_type.IsBool()) {
    return new ast::IfStmt{cond, std::move(on_true), std::move(on_false)};
  } else {
    throw err::NonBoolCondition{cond_type};
  }
}
