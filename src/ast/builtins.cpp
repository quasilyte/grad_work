#include "ast/builtins.hpp"

#include "ast/visitor.hpp"

using namespace ast;

Operation::Operation(ArgList&& operands): operands{operands} {}

void Sum::Accept(Visitor* v) { v->Visit(this); }
void Sub::Accept(Visitor* v) { v->Visit(this); }
void Mul::Accept(Visitor* v) { v->Visit(this); }
void Lt::Accept(Visitor* v) { v->Visit(this); }
void Gt::Accept(Visitor* v) { v->Visit(this); }

LambdaExpr::LambdaExpr(sym::Type::Id id): id{id} {}

void LambdaExpr::Accept(Visitor* v) { v->Visit(this); }

FuncCall::FuncCall(sym::Func* func, ArgList&& args):
func{func}, args{args} {}

void FuncCall::Accept(Visitor* v) { v->Visit(this); }

VarCall::VarCall(dt::StrView name, sym::Func* func, ArgList&& args):
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
