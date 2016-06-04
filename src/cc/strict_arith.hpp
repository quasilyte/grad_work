#pragma once

#include "ast/binary_ops.hpp"
#include "ast/typedefs.hpp"

namespace ast {
  struct Node;
}

namespace cc {
# define Node ast::Node
# define NodeList ast::NodeList

  Node* strict_sum(ast::BinaryNode);
  Node* strict_sub(ast::BinaryNode);
  Node* strict_mul(ast::BinaryNode);
  Node* strict_div(ast::BinaryNode);

  Node* strict_eq(ast::BinaryNode);

  Node* strict_if_stmt(Node* cond, NodeList&& on_true, NodeList&& on_false);

# undef Node
# undef NodeList
}
