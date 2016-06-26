#include <cc/strict/arith.hpp>

#include <ast/builtins.hpp>
#include <err/type_errors.hpp>

using namespace cc;
using namespace ast;

Node* num_type_checked(BinaryOp* node) {
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

Node* cc::strict_sum(BinaryNode operands) {
  return num_type_checked(new ast::Sum{operands, operands.lhs->Type()});
}

Node* cc::strict_sub(BinaryNode operands) {
  return num_type_checked(new Sub{operands, operands.lhs->Type()});
}

Node* cc::strict_mul(BinaryNode operands) {
  return num_type_checked(new Mul{operands, operands.lhs->Type()});
}

Node* cc::strict_div(BinaryNode operands) {
  return num_type_checked(new Div{operands, operands.lhs->Type()});
}

/*
Node* cc::strict_sum_assign(dt::StrView recv_name, Node* expr) {

}
*/

Node* cc::strict_eq(BinaryNode operands) {
  return num_type_checked(new ast::NumEq{operands});
}

