#include "ast/cond.hpp"

using namespace ast;

If::If(Node *cond, Node *on_true, Node *on_false):
Node{sym::least_upper_bound(on_true->Type(), on_false->Type())},
cond{cond}, on_true{on_true}, on_false{on_false} {}

void If::GenerateCode(const sym::Module& module, const io::FileWriter& fw) {
  fw.Write("(");
  cond->GenerateCode(module, fw);
  fw.Write(")?(");
  on_true->GenerateCode(module, fw);
  fw.Write("):(");
  on_false->GenerateCode(module, fw);
  fw.Write(")");
}
