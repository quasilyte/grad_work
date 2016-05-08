#include "ast/defs.hpp"

#include "sym/sym.hpp"

using namespace ast;

Let::Let(lex::Token name, Node* assignment):
name{name}, assignment{assignment} {}

// `$type $name{$assignment};`
void Let::GenerateCode(const sym::Module& module, const io::FileWriter& fw) {
  if (name.IsList()) {
    throw "cant defun yet";
  } else if (name.IsWord()) {
    auto type = module.Symbol(name.AsStrView());

    fw.Write(type.Name()); // #FIXME: type.name should be CstrView
    fw.Write(' ');
    fw.WriteMangled(name.AsStrView());
    fw.Write('{');
    assignment->GenerateCode(module, fw);
    fw.Write("};", 2);
  } else {
    throw "def symbol must be of type word";
  }
}

Set::Set(lex::Token name, Node* assignment):
name{name}, assignment{assignment} {}

// `$name=$assignment;`
void Set::GenerateCode(const sym::Module& module, const io::FileWriter& fw) {
  if (name.IsWord()) {
    fw.Write(name.AsStrView());
    fw.Write('=');
    assignment->GenerateCode(module, fw);
    fw.Write(';');
  } else {
    throw "name for set! must be word";
  }
}
