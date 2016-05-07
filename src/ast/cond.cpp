#include "ast/cond.hpp"

using namespace ast;

If::If(Node *cond, Node *on_true, Node *on_false):
Node{},
cond{cond}, on_true{on_true}, on_false{on_false} {}

void If::GenerateCode(const io::FileWriter& fw) {
  fw.Write("(");
  cond->GenerateCode(fw);
  fw.Write(")?(");
  on_true->GenerateCode(fw);
  fw.Write("):(");
  on_false->GenerateCode(fw);
  fw.Write(")");
}
