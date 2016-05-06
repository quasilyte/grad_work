#pragma once

#include "ast/node.hpp"

namespace ast {
  struct BinOp;
  struct BinAdd;
  struct BinSub;
}

struct ast::BinOp: public Node {
  BinOp(Node *lhs, Node *rhs);

protected:
  void write(io::FileWriter*, const char *op);

private:
  Node *lhs;
  Node *rhs;
};

struct ast::BinAdd: public BinOp {
  using BinOp::BinOp;
  void generate_code(io::FileWriter*);
  int type_check() noexcept;
};

struct ast::BinSub: public BinOp {
  using BinOp::BinOp;
  void generate_code(io::FileWriter*);
  int type_check() noexcept;
};
