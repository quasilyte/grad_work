#include "bin_ops.hpp"

ast::BinOp::BinOp(Node *lhs, Node *rhs):
lhs{lhs}, rhs{rhs} {}

void ast::BinOp::write(io::FileWriter *fw, const char *op) {
  lhs->generate_code(fw);
  fw->write(op);
  rhs->generate_code(fw);
}

void ast::BinAdd::generate_code(io::FileWriter *fw) {
  write(fw, "+");
}

int ast::BinAdd::type_check() noexcept {
  return 0;
}

void ast::BinSub::generate_code(io::FileWriter *fw) {
  write(fw, "-");
}
