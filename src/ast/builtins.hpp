#pragma once

#include "ast/node.hpp"
#include "dt/str_view.hpp"
#include "sym/type.hpp"
#include "sym/param.hpp"
#include <vector>

namespace sym {
  struct NamedFn;
  struct MultiFn;
  struct Fn;
}

namespace ast {
  struct Each;
  struct Operation;
  struct Sum;
  struct Sub;
  struct Mul;
  struct Lt;
  struct Gt;
  struct LambdaExpr;
  struct FuncCall;
  struct VarCall;
  struct DynamicCall;
  struct AttrAccess;
  struct Intrinsic;
  struct IntrinsicCall1;
}

struct ast::Each: public Node {
  Each(Node* init, Node* body, sym::NamedFn*, sym::NamedFn*, sym::NamedFn*, dt::StrView);

  void Accept(Visitor*);

  Node* init;
  Node* body;
  sym::NamedFn* next_fn;
  sym::NamedFn* has_next_fn;
  sym::NamedFn* current_fn;
  dt::StrView iter_name;
};

struct ast::Operation: public Node {
  typedef std::vector<Node*> ArgList;

  Operation(ArgList&&);

  ArgList operands;
};

struct ast::Sum: public Operation {
  Sum(ArgList&&);
  void Accept(Visitor*);
};

struct ast::Mul: public Operation {
  Mul(ArgList&&);
  void Accept(Visitor*);
};

struct ast::Sub: public Operation {
  Sub(ArgList&&);
  void Accept(Visitor*);
};

struct ast::Lt: public Operation {
  Lt(ArgList&&);
  void Accept(Visitor*);
};

struct ast::Gt: public Operation {
  Gt(ArgList&&);
  void Accept(Visitor*);
};

struct ast::LambdaExpr: public Node {
  LambdaExpr(sym::Type);

  void Accept(Visitor*);

  sym::Type type;
};

struct ast::FuncCall: public Node {
  typedef std::vector<Node*> ArgList;

  FuncCall(sym::NamedFn*, ArgList&&);

  void Accept(Visitor*);

  sym::NamedFn* func;
  std::vector<Node*> args;
};

struct ast::VarCall: public Node {
  typedef std::vector<Node*> ArgList;

  VarCall(dt::StrView name, sym::Fn*, ArgList&&);

  void Accept(Visitor*);

  dt::StrView name;
  sym::Fn* func;
  std::vector<Node*> args;
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

struct ast::DynamicCall: public Node {
  typedef std::vector<Node*> ArgList;

  DynamicCall(sym::MultiFn*, ArgList&&);

  void Accept(Visitor*);

  sym::MultiFn* func;
  std::vector<Node*> args;
};
