#pragma once

#include <ast/binary_ops.hpp>
#include <ast/typedefs.hpp>
#include <dt/str_view.hpp>

namespace ast {
  struct Node;
}

namespace cc {
# define Node ast::Node

  Node* strict_sum(ast::BinaryNode);
  Node* strict_sub(ast::BinaryNode);
  Node* strict_mul(ast::BinaryNode);
  Node* strict_div(ast::BinaryNode);

  Node* strict_eq(ast::BinaryNode);

# undef Node
}
