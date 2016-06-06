#pragma once

#include <ast/node.hpp>

namespace ast {
  struct BinaryNode;

  struct BinaryOp;

  struct ArithOp;
  struct Sum;
  struct Sub;
  struct Mul;
  struct Div;

  struct LogicalOp;
  struct NumLt;
  struct NumGt;
  struct NumEq;
}

struct ast::BinaryNode {
  ast::Node* lhs;
  ast::Node* rhs;
};

struct ast::BinaryOp: Node {
  BinaryOp(ast::BinaryNode);
  BinaryOp(Node* lhs, Node* rhs);

  ast::BinaryNode operands;
};

struct ast::ArithOp: BinaryOp {
  ArithOp(BinaryNode, sym::Type);
  ArithOp(Node* lhs, Node* rhs, sym::Type);

  sym::Type Type() override;

  sym::Type type;
};

struct ast::LogicalOp: BinaryOp {
  using BinaryOp::BinaryOp;

  sym::Type Type() override;
};

#define GEN_ARITH_OP(NAME) \
  struct ast::NAME: ArithOp { \
    using ArithOp::ArithOp; \
    void Accept(Visitor*) override; \
    const char* Symbol() override; \
  }

GEN_ARITH_OP(Sum);
GEN_ARITH_OP(Mul);
GEN_ARITH_OP(Sub);
GEN_ARITH_OP(Div);

#define GEN_LOGICAL_OP(NAME) \
  struct ast::NAME: LogicalOp { \
    using LogicalOp::LogicalOp; \
    void Accept(Visitor*) override; \
    const char* Symbol() override; \
  }

GEN_LOGICAL_OP(NumLt);
GEN_LOGICAL_OP(NumGt);
GEN_LOGICAL_OP(NumEq);

#undef GEN_ARITH_OP
#undef GEN_LOGICAL_OP
