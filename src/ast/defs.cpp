#include "ast/defs.hpp"

#include "sym/sym.hpp"
#include "ast/visitor.hpp"

using namespace ast;

/*
DefVar::DefVar(dt::StrView name, Node* assignment):
name{name}, assignment{assignment} {}

// `$type $name{$assignment};`
void DefVar::GenerateCode(const sym::Module* module, const io::FileWriter& fw) {
  auto type = module->Local(name).type;

  fw.Write(type->Name()); // #FIXME: type.name should be CstrView
  fw.Write(' ');
  fw.Write(name);
  fw.Write('{');
  assignment->GenerateCode(module, fw);
  fw.Write("};", 2);
}

DefLocal::DefLocal(const dt::StrView* name, Node* assignment):
name{name}, assignment{assignment} {}

// `$type $name{$assignment};`
void DefLocal::GenerateCode(const sym::Module* module, const io::FileWriter& fw) {
  fw.Write(assignment->Type()->Name()); // #FIXME: type.name should be CstrView
  fw.Write(' ');
  fw.Write(*name);
  fw.Write('{');
  assignment->GenerateCode(module, fw);
  fw.Write("};", 2);
}

DefFunc::DefFunc(lex::Token name, std::vector<lex::Token>&& params, Node* body):
name{name}, params{params}, body{body} {}

void DefFunc::GenerateCode(const sym::Module* module, const io::FileWriter& fw) {
  auto type = body->Type();

  fw.Write(type->Name());
  fw.Write(' ');
  fw.Write(name.AsStrView());
  fw.Write('(');
  for (uint i = 0; i < params.size() - 1; ++i) {
    fw.Write(params[i].AsStrView());
    fw.Write(',');
  }
  fw.Write(params.back().AsStrView());
  fw.Write("){", 2);
  fw.Write("return ", 7);
  body->GenerateCode(module, fw);
  fw.Write(';');
  fw.Write('}');
}
*/

SetGlobal::SetGlobal(dt::StrView name, Node* value):
name{name}, value{value} {}

void SetGlobal::Accept(Visitor* v) { v->Visit(this); }

const dt::StrView& SetGlobal::Name() const noexcept {
  return name;
}

Node* SetGlobal::Value() const noexcept {
  return value;
}

DefLocal::DefLocal(const dt::StrView* name, Node* value, sym::Type ty):
name{name}, value{value}, type{ty} {}

void DefLocal::Accept(Visitor* v) { v->Visit(this); }

const dt::StrView* DefLocal::Name() const noexcept {
  return name;
}

Node* DefLocal::Value() const noexcept {
  return value;
}

sym::Type DefLocal::Type() const noexcept {
  return type;
}
