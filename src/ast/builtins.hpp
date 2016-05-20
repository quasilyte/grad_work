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
  struct VarCall;
  struct AttrAccess;
  struct Intrinsic;
  struct IntrinsicCall1;
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

struct ast::FuncCall: public Node {
  typedef std::vector<Node*> ArgList;

  FuncCall(sym::Func*, ArgList&&);

  void Accept(Visitor*);

  sym::Func* func;
  std::vector<Node*> args;
};

struct ast::VarCall: public FuncCall {
  VarCall(dt::StrView name, sym::Func*, ArgList&&);

  void Accept(Visitor*);

  dt::StrView name;
};

struct ast::AttrAccess: public Node {
  AttrAccess(dt::StrView, sym::Param*);

  void Accept(Visitor*);

  dt::StrView obj_name;
  sym::Param* attr;
};

struct ast::Intrinsic: public Node {
  Intrinsic(sym::Type);

  void Accept(Visitor*);

  sym::Type type;
};

struct ast::IntrinsicCall1: public Node {
  IntrinsicCall1(sym::Type, Node* arg);

  void Accept(Visitor*);

  Node* arg;
  sym::Type type;
};
