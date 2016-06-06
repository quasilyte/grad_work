#pragma once

#include "ast/node.hpp"
#include "dt/str_view.hpp"
#include "sym/type.hpp"
#include "sym/param.hpp"
#include <ast/typedefs.hpp>
#include <deps/cxx/vector.hpp>

namespace sym {
  struct NamedFn;
  struct MultiFn;
  struct MonoFn;
  struct Fn;
}

namespace ast {
  struct Each;
  struct SumAssign;
  struct LambdaExpr;
  struct FuncCall;
  struct MonoFnCall;
  struct VarCall;
  struct DynamicCall;
  struct AttrAccess;
  struct Intrinsic;
  struct IntrinsicCall1;
  struct Var;
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

struct ast::SumAssign: Node {
  SumAssign(dt::StrView target, Node* val);

  void Accept(Visitor*) override;
  sym::Type Type() override;

  dt::StrView target;
  Node* val;
};

struct ast::LambdaExpr: public Node {
  LambdaExpr(sym::Type);

  void Accept(Visitor*);

  sym::Type type;
};

struct ast::FuncCall: public Node {
  FuncCall(sym::NamedFn*, ArgList&&);

  void Accept(Visitor*);

  sym::NamedFn* func;
  ArgList args;
};

struct ast::MonoFnCall: public Node {
  MonoFnCall(sym::MonoFn*, ArgList&&);

  void Accept(Visitor*) override;
  sym::Type Type() override;

  sym::MonoFn* fn;
  ArgList args;
};

struct ast::VarCall: public Node {
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
  DynamicCall(sym::MultiFn*, ArgList&&);

  void Accept(Visitor*);

  sym::MultiFn* func;
  std::vector<Node*> args;
};

struct ast::Var: public Node {
  Var(dt::StrView, sym::Type);

  void Accept(Visitor*) override;
  sym::Type Type() override;

  const dt::StrView name;
  const sym::Type type;
};
