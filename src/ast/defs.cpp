#include "ast/defs.hpp"

using namespace ast;

Define::Define(lex::Token name, Node* assignment):
name{name}, assignment{assignment} {}

void Define::GenerateCode(const io::FileWriter& fw) {
  if (name.IsList()) {
    throw "cant defun yet";
  } else if (name.IsWord()) {
    fw.Write(assignment->Type().Name());
    fw.Write(' ');
    fw.Write(name.Val(), name.Len());
    fw.Write('=');
    assignment->GenerateCode(fw);
    fw.Write(';');
  } else {
    throw "def symbol must be of type word";
  }
}

Set::Set(lex::Token name, Node* assignment):
name{name}, assignment{assignment} {}

void Set::GenerateCode(const io::FileWriter& fw) {
  if (name.IsWord()) {
    // #TODO: check type
    fw.Write(name.Val(), name.Len());
    fw.Write('=');
    assignment->GenerateCode(fw);
    fw.Write(';');
  } else {
    throw "name for set! must be word";
  }
}
