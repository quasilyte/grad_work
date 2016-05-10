#include "ast/defs.hpp"

#include "sym/sym.hpp"

using namespace ast;

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

Set::Set(lex::Token name, Node* assignment):
name{name}, assignment{assignment} {}

// `$name=$assignment;`
void Set::GenerateCode(const sym::Module* module, const io::FileWriter& fw) {
  if (name.IsWord()) {
    fw.Write(name.AsStrView());
    fw.Write('=');
    assignment->GenerateCode(module, fw);
    fw.Write(';');
  } else {
    throw "name for set! must be word";
  }
}
