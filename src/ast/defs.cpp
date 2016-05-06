#include "ast/defs.hpp"

using namespace ast;

Define::Define(lex::Token name, Node* assignment):
name{name}, assignment{assignment} {}

void Define::generate_code(io::FileWriter* fw) {
  if (name.is_list()) {
    throw "cant defun yet";
  } else if (name.is_word()) {
    fw->write(assignment->get_type_name());
    fw->write(' ');
    fw->write(name.get_val(), name.get_len());
    fw->write('=');
    assignment->generate_code(fw);
    fw->write(';');
  } else {
    throw "def symbol must be of type word";
  }
}

Set::Set(lex::Token name, Node* assignment):
name{name}, assignment{assignment} {}

void Set::generate_code(io::FileWriter* fw) {
  if (name.is_word()) {
    // #TODO: check type
    fw->write(name.get_val(), name.get_len());
    fw->write('=');
    assignment->generate_code(fw);
    fw->write(';');
  } else {
    throw "name for set! must be word";
  }
}
