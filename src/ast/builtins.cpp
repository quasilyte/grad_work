#include "ast/builtins.hpp"

#include "ast/visitor.hpp"

using namespace ast;

/*
FuncCall::FuncCall(const sym::Type* type, lex::Token name, std::vector<Node *> &&args):
type{type}, name{name}, args{args} {}

void FuncCall::GenerateCode(const sym::Module* module, const io::FileWriter& fw) {
  fw.Write(name.AsStrView());
  fw.Write('(');
  for (uint i = 0; i < args.size() - 1; ++i) {
    args[i]->GenerateCode(module, fw);
    fw.Write(',');
  }
  args.back()->GenerateCode(module, fw);
  fw.Write(')');
}

const sym::Type* FuncCall::Type() {
  return type;
}
*/

Sum::Sum(std::vector<Node*>&& operands): operands{operands} {}

void Sum::Accept(Visitor* v) { v->Visit(this); }

FuncCall::FuncCall(dt::StrView name, std::vector<Node*>&& args, sym::Type ty):
name{name}, args{args}, ty{ty} {}

void FuncCall::Accept(Visitor* v) { v->Visit(this); }

AttrAccess::AttrAccess(dt::StrView obj_name, sym::Param* attr):
obj_name{obj_name}, attr{attr} {}

void AttrAccess::Accept(Visitor* v) { v->Visit(this); }

/*
void Sum::GenerateCode(const sym::Module* module, const io::FileWriter& fw) {
  if (operands.size() == 1) {
    operands[0]->GenerateCode(module, fw);
  } else {
    fw.Write('(');
    for (uint i = 0; i < operands.size() - 1; ++i) {
      if (!operands[i]->Type()->Arith()) {
        throw "(+) defined only for {any, num, real, int} types";
      }
      operands[i]->GenerateCode(module, fw);
      fw.Write('+');
    }
    operands.back()->GenerateCode(module, fw);

    fw.Write(')');
  }
}

const sym::Type* Sum::Type() {
  bool int_typed = true;

  for (Node* operand : operands) {
    if (operand->Type()->IsReal()) {
      return &sym::Type::REAL;
    }

    if (operand->Type()->IsNum() || operand->Type()->IsAny()) {
      int_typed = false;
    }
  }

  return int_typed ? &sym::Type::INT : &sym::Type::NUM;
}
*/
