#include "ast/atoms.hpp"

using namespace ast;
using namespace sym;

Type Int::RT_TYPE{1, "long", Type::NUM};
Int::Int(lex::Token tok): Node{RT_TYPE}, tok{tok} {}

void Int::generate_code(io::FileWriter* fw) {
  fw->write(tok.get_val(), tok.get_len());
}

Type Real::RT_TYPE{1, "double", Type::NUM};
Real::Real(lex::Token tok): Node{RT_TYPE}, tok{tok} {}

void Real::generate_code(io::FileWriter* fw) {
  fw->write(tok.get_val(), tok.get_len());
}

