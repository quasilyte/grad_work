#include "ast/builtins.hpp"

using namespace ast;

Sum::Sum(std::vector<Node*> operands): operands{operands} {}

void Sum::GenerateCode(const sym::Module& module, const io::FileWriter& fw) {
  if (operands.size() == 1) {
    operands[0]->GenerateCode(module, fw);
  } else {
    fw.Write('(');
    for (uint i = 0; i < operands.size() - 1; ++i) {
      if (!operands[i]->Type().Arith()) {
        throw "(+) defined only for {any, num, real, int} types";
      }
      operands[i]->GenerateCode(module, fw);
      fw.Write('+');
    }
    operands.back()->GenerateCode(module, fw);

    fw.Write(')');
  }
}

const sym::Type& Sum::Type() {
  bool int_typed = true;

  for (Node* operand : operands) {
    if (operand->Type().IsReal()) {
      return sym::Type::REAL;
    }

    if (operand->Type().IsNum() || operand->Type().IsAny()) {
      int_typed = false;
    }
  }

  return int_typed ? sym::Type::INT : sym::Type::NUM;
}