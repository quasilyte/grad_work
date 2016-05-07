#include "ast/cond.hpp"

using namespace ast;

If::If(Node *cond, Node *on_true, Node *on_false):
cond{cond}, on_true{on_true}, on_false{on_false} {}

// `($cond)?($on_true):($on_false)`
void If::GenerateCode(const sym::Module& module, const io::FileWriter& fw) {
  fw.Write("(");
  cond->GenerateCode(module, fw);
  fw.Write(")?(");
  on_true->GenerateCode(module, fw);
  fw.Write("):(");
  on_false->GenerateCode(module, fw);
  fw.Write(")");
}

const sym::Type& If::Type() {
  return on_false->Type().Merge(on_true->Type());
}
