#include "ast/defs.hpp"

using namespace ast;

Define::Define(lex::Token name, Node* assignment):
Node{assignment->Type()},
name{name}, assignment{assignment} {}

void Define::GenerateCode(const sym::Module& module, const io::FileWriter& fw) {
  if (name.IsList()) {
    throw "cant defun yet";
  } else if (name.IsWord()) {
    auto type = module.Symbol(dt::StrView{name.Val(), name.Len()});

    fw.Write(type.Name());
    fw.Write(' ');
    fw.Write(name.Val(), name.Len());
    fw.Write('=');
    assignment->GenerateCode(module, fw);
    fw.Write(';');
  } else {
    throw "def symbol must be of type word";
  }
}

Set::Set(lex::Token name, Node* assignment):
name{name}, assignment{assignment} {}

void Set::GenerateCode(const sym::Module& module, const io::FileWriter& fw) {
  if (name.IsWord()) {
    // #TODO: check type
    fw.Write(name.Val(), name.Len());
    fw.Write('=');
    assignment->GenerateCode(module, fw);
    fw.Write(';');
  } else {
    throw "name for set! must be word";
  }
}
