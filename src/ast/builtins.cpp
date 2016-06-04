#include "ast/builtins.hpp"

#include "ast/visitor.hpp"
#include "sym/fn.hpp"

using namespace ast;

Each::Each(
  Node *init,
  Node *body,
  sym::NamedFn* next_fn,
  sym::NamedFn* has_next_fn,
  sym::NamedFn* current_fn,
  dt::StrView iter_name
):
init{init},
body{body},
next_fn{next_fn},
has_next_fn{has_next_fn},
current_fn{current_fn},
iter_name{iter_name} {}

void Each::Accept(Visitor* v) { v->Visit(this); }

SumAssign::SumAssign(dt::StrView target, Node *val):
target{target}, val{val} {}

void SumAssign::Accept(Visitor* v) { v->Visit(this); }

sym::Type SumAssign::Type() {
  return sym::Type::Void();
}

LambdaExpr::LambdaExpr(sym::Type type): type{type} {}

void LambdaExpr::Accept(Visitor* v) { v->Visit(this); }

FuncCall::FuncCall(sym::NamedFn* func, ArgList&& args):
func{func}, args{args} {}

void FuncCall::Accept(Visitor* v) { v->Visit(this); }

MonoFnCall::MonoFnCall(sym::MonoFn* fn, ArgList&& args):
fn{fn}, args{args} {}

void MonoFnCall::Accept(Visitor* v) { v->Visit(this); }

sym::Type MonoFnCall::Type() {
  return fn->ret_type;
}

VarCall::VarCall(dt::StrView name, sym::Fn* func, ArgList&& args):
name{name}, func{func}, args{args} {}

void VarCall::Accept(Visitor* v) { v->Visit(this); }

AttrAccess::AttrAccess(dt::StrView obj_name, sym::Param* attr):
obj_name{obj_name}, attr{attr} {}

void AttrAccess::Accept(Visitor* v) { v->Visit(this); }

Intrinsic::Intrinsic(sym::Type ty): type{ty} {}

void Intrinsic::Accept(Visitor* v) { v->Visit(this); }

IntrinsicCall1::IntrinsicCall1(sym::Type ty, Node* arg):
arg{arg}, type{ty} {}

void IntrinsicCall1::Accept(Visitor* v) { v->Visit(this); }

DynamicCall::DynamicCall(sym::MultiFn* func, ArgList&& args):
func{func}, args{args} {}

void DynamicCall::Accept(Visitor* v) { v->Visit(this); }

Var::Var(dt::StrView name, sym::Type type):
name{name}, type{type} {}

void Var::Accept(Visitor* v) { v->Visit(this); }

sym::Type Var::Type() {
  return type;
}
