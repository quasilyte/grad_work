#include "ast/atoms.hpp"

using namespace ast;

Int::Int(lex::Token tok): Node{RT_TYPE}, tok{tok} {}

void Int::generate_code(io::FileWriter* fw) {
  fw->write(tok.get_val(), tok.get_len());
}

const char* Int::get_type_name() const {
  return "long";
}

Real::Real(lex::Token tok): Node{RT_TYPE}, tok{tok} {}

void Real::generate_code(io::FileWriter* fw) {
  fw->write(tok.get_val(), tok.get_len());
}

const char* Real::get_type_name() const {
  return "double";
}
