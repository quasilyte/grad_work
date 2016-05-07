#include "ast/cond.hpp"

using namespace ast;

If::If(Node *cond, Node *on_true, Node *on_false):
Node{},
cond{cond}, on_true{on_true}, on_false{on_false} {}

void If::generate_code(io::FileWriter* fw) {
  fw->write("(");
  cond->generate_code(fw);
  fw->write(")?(");
  on_true->generate_code(fw);
  fw->write("):(");
  on_false->generate_code(fw);
  fw->write(")");
}
