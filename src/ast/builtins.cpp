#include "ast/builtins.hpp"

#include "ast/visitor.hpp"

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

Operation::Operation(ArgList&& operands): operands{operands} {}

Sum::Sum(ArgList&& operands): Operation{std::move(operands)} {
  if (operands.size() < 1) {
    throw "Sum: min arity is 1";
  }
}
void Sum::Accept(Visitor* v) { v->Visit(this); }

Sub::Sub(ArgList&& operands): Operation{std::move(operands)} {
  if (operands.size() < 1) {
    throw "Sub: min arity is 1";
  }
}
void Sub::Accept(Visitor* v) { v->Visit(this); }

Mul::Mul(ArgList&& operands): Operation{std::move(operands)} {
  if (operands.size() < 1) {
    throw "Mul: min arity is 1";
  }
}
void Mul::Accept(Visitor* v) { v->Visit(this); }

Lt::Lt(ArgList&& operands): Operation{std::move(operands)} {
  if (operands.size() < 2) {
    throw "Lt: min arity is 2";
  }
}
void Lt::Accept(Visitor* v) { v->Visit(this); }

Gt::Gt(ArgList&& operands): Operation{std::move(operands)} {
  if (operands.size() < 2) {
    throw "Gt: min arity is 2";
  }
}
void Gt::Accept(Visitor* v) { v->Visit(this); }

LambdaExpr::LambdaExpr(sym::TypeId id): id{id} {}

void LambdaExpr::Accept(Visitor* v) { v->Visit(this); }

FuncCall::FuncCall(sym::NamedFn* func, ArgList&& args):
func{func}, args{args} {}

void FuncCall::Accept(Visitor* v) { v->Visit(this); }

VarCall::VarCall(dt::StrView name, sym::NamedFn* func, ArgList&& args):
FuncCall{func, std::move(args)}, name{name} {}

void VarCall::Accept(Visitor* v) { v->Visit(this); }

AttrAccess::AttrAccess(dt::StrView obj_name, sym::Param* attr):
obj_name{obj_name}, attr{attr} {}

void AttrAccess::Accept(Visitor* v) { v->Visit(this); }

Intrinsic::Intrinsic(sym::Type ty): type{ty} {}

void Intrinsic::Accept(Visitor* v) { v->Visit(this); }

IntrinsicCall1::IntrinsicCall1(sym::Type ty, Node* arg):
arg{arg}, type{ty} {}

void IntrinsicCall1::Accept(Visitor* v) { v->Visit(this); }
