#include "ast/binary_ops.hpp"

#include "ast/visitor.hpp"

using namespace ast;

BinaryOp::BinaryOp(BinaryNode operands):
operands{operands.lhs, operands.rhs} {}

BinaryOp::BinaryOp(Node* lhs, Node* rhs): operands{lhs, rhs} {}

ArithOp::ArithOp(BinaryNode operands, sym::Type type):
BinaryOp{operands.lhs, operands.rhs}, type{type} {}

ArithOp::ArithOp(Node *lhs, Node *rhs, sym::Type type):
BinaryOp{lhs, rhs}, type{type} {}

sym::Type ArithOp::Type() {
  return type;
}

#define GEN_BINARY_OP(NAME, SYMBOL) \
  void ast::NAME::Accept(Visitor* v) { v->Visit(this); } \
  const char* ast::NAME::Symbol() { return SYMBOL; }

GEN_BINARY_OP(Sum, "+")
GEN_BINARY_OP(Mul, "*")
GEN_BINARY_OP(Sub, "-")
GEN_BINARY_OP(Div, "/")

sym::Type LogicalOp::Type() {
  return sym::Type::Bool();
}

GEN_BINARY_OP(NumGt, ">")
GEN_BINARY_OP(NumLt, "<")
GEN_BINARY_OP(NumEq, "==")

