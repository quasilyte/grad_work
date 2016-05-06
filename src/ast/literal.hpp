#pragma once

#include "ast/node.hpp"

namespace ast {
  struct Integer;
  struct Real;
  struct String;
}

struct ast::Integer: Node {
  Integer(int);
  void generate_code(io::FileWriter*);
  int type_check() noexcept;

  int value;
};
