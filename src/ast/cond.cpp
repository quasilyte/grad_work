#include "ast/cond.hpp"

using namespace ast;

If::If(Node *cond, Node *on_true, Node *on_false):
cond{cond}, on_true{on_true}, on_false{on_false} {}

const char* If::get_type_name() const {
  if (on_true->get_type() == on_false->get_type()) {
    return on_true->get_type_name();
  } else {
    throw "type mismatch";
  }
}

void If::generate_code(io::FileWriter* fw) {
  fw->write("(");
  cond->generate_code(fw);
  fw->write(")?(");
  on_true->generate_code(fw);
  fw->write("):(");
  on_false->generate_code(fw);
  fw->write(")");
}
