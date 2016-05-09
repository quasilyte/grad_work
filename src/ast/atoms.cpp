#include "ast/atoms.hpp"

#include "sym/sym.hpp"

using namespace ast;
using namespace sym;

Int::Int(lex::Token tok): tok{tok} {}

void Int::GenerateCode(const sym::Module&, const io::FileWriter& fw) {
  fw.Write(tok.AsStrView());
  fw.Write("_i", 2);
}

const Type* Int::Type() {
  return &sym::Type::INT;
}

Real::Real(lex::Token tok): tok{tok} {}

void Real::GenerateCode(const sym::Module&, const io::FileWriter& fw) {
  fw.Write(tok.AsStrView());
  fw.Write("_r", 2);
}

const Type* Real::Type() {
  return &sym::Type::REAL;
}

Str::Str(lex::Token tok): tok{tok} {}

void Str::GenerateCode(const sym::Module&, const io::FileWriter& fw) {
  fw.Write(tok.AsStrView());
}

const Type* Str::Type() {
  return &sym::Type::STR;
}

Var::Var(const dt::StrView* name, const sym::Type* type):
name{name}, type{type} {}

void Var::GenerateCode(const sym::Module&, const io::FileWriter& fw) {
  fw.Write(*name);
}

const Type* Var::Type() {
  return type;
}
