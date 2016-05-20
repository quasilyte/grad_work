#pragma once

#include "ast/node.hpp"
#include "dt/str_view.hpp"
#include "sym/type.hpp"
#include "sym/param.hpp"
#include <vector>

namespace sym {
  struct Func;
}

namespace ast {
  struct Operation;
  struct Sum;
  struct Sub;
  struct Mul;
  struct Lt;
  struct Gt;
  struct FuncCall;
  struct AttrAccess;
  struct TypeCast;
}

struct ast::Operation: public Node {
  typedef std::vector<Node*> ArgList;

  Operation(ArgList&&);

  ArgList operands;
};

struct ast::Sum: public Operation {
  using Operation::Operation;
  void Accept(Visitor*);
};

struct ast::Mul: public Operation {
  using Operation::Operation;
  void Accept(Visitor*);
};

struct ast::Sub: public Operation {
  using Operation::Operation;
  void Accept(Visitor*);
};

struct ast::Lt: public Operation {
  using Operation::Operation;
  void Accept(Visitor*);
};

struct ast::Gt: public Operation {
  using Operation::Operation;
  void Accept(Visitor*);
};

// struct ast::Eq

struct ast::FuncCall: public Node {
  typedef std::vector<Node*> ArgList;

  FuncCall(sym::Func*, ArgList&& args);

  void Accept(Visitor*);

  sym::Func* func;
  std::vector<Node*> args;
};

struct ast::AttrAccess: public Node {
  AttrAccess(dt::StrView, sym::Param*);

  void Accept(Visitor*);

  dt::StrView obj_name;
  sym::Param* attr;
};

struct ast::TypeCast: public Node {
  TypeCast(Node* expr, sym::Type from, sym::Type to);

  void Accept(Visitor*);

  Node* expr;
  sym::Type from;
  sym::Type to;
};
