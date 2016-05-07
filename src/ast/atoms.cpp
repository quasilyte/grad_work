#include "ast/atoms.hpp"

using namespace ast;
using namespace sym;

Type Int::RT_TYPE{1, "long", Type::NUM};
Int::Int(lex::Token tok): Node{RT_TYPE}, tok{tok} {}

void Int::GenerateCode(const io::FileWriter& fw) {
  fw.Write(tok.Val(), tok.Len());
}

Type Real::RT_TYPE{1, "double", Type::NUM};
Real::Real(lex::Token tok): Node{RT_TYPE}, tok{tok} {}

void Real::GenerateCode(const io::FileWriter& fw) {
  fw.Write(tok.Val(), tok.Len());
}

