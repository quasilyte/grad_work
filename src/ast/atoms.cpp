#include "ast/atoms.hpp"

#include "sym/sym.hpp"

using namespace ast;
using namespace sym;

Int::Int(lex::Token tok): tok{tok} {}

void Int::GenerateCode(const sym::Module&, const io::FileWriter& fw) {
  fw.Write(tok.AsStrView());
  fw.Write("_i", 2);
}

const sym::Type& Int::Type() {
  return sym::Type::INT;
}

Real::Real(lex::Token tok): tok{tok} {}

void Real::GenerateCode(const sym::Module&, const io::FileWriter& fw) {
  fw.Write(tok.AsStrView());
  fw.Write("_r", 2);
}

const sym::Type& Real::Type() {
  return sym::Type::REAL;
}

Str::Str(lex::Token tok): tok{tok} {}

void Str::GenerateCode(const sym::Module&, const io::FileWriter& fw) {
  fw.Write(tok.AsStrView());
}

const sym::Type& Str::Type() {
  return sym::Type::STR;
}

Var::Var(const sym::Type& type, lex::Token tok): type{type}, tok{tok} {}

void Var::GenerateCode(const sym::Module&, const io::FileWriter& fw) {
  fw.WriteMangled(tok.AsStrView());
}

const sym::Type& Var::Type() {
  return type;
}
