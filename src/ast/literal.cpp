#include "ast/literal.hpp"

ast::Integer::Integer(int value):
value{value} {}

void ast::Integer::generate_code(io::FileWriter *fw) {
}

int ast::Integer::type_check() noexcept {
  return value;
}
