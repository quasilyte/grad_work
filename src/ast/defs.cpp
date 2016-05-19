#include "ast/defs.hpp"

#include "sym/sym.hpp"
#include "ast/visitor.hpp"

using namespace ast;

SetVar::SetVar(dt::StrView name, Node* value):
name{name}, value{value} {}

void SetVar::Accept(Visitor* v) { v->Visit(this); }

SetAttr::SetAttr(dt::StrView obj_name, sym::Param *attr, Node *value):
obj_name{obj_name}, attr{attr}, value{value} {}

void SetAttr::Accept(Visitor* v) { v->Visit(this); }

DefVar::DefVar(dt::StrView name, Node* value, sym::Type ty):
name{name}, value{value}, type{ty} {}

void DefVar::Accept(Visitor* v) { v->Visit(this); }
