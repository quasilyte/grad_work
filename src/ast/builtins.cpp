#include "ast/builtins.hpp"

#include "ast/visitor.hpp"

using namespace ast;

Operation::Operation(ArgList&& operands): operands{operands} {}

void Sum::Accept(Visitor* v) { v->Visit(this); }
void Sub::Accept(Visitor* v) { v->Visit(this); }
void Lt::Accept(Visitor* v) { v->Visit(this); }
void Gt::Accept(Visitor* v) { v->Visit(this); }

FuncCall::FuncCall(sym::Func* func, ArgList&& args):
func{func}, args{args} {}

void FuncCall::Accept(Visitor* v) { v->Visit(this); }

AttrAccess::AttrAccess(dt::StrView obj_name, sym::Param* attr):
obj_name{obj_name}, attr{attr} {}

void AttrAccess::Accept(Visitor* v) { v->Visit(this); }
