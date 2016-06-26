#pragma once

#include <dt/str_view.hpp>
#include <ast/typedefs.hpp>

namespace ast {
  struct Node;
}

namespace cc {
# define Node ast::Node
# define NodeList ast::NodeList

  Node* strict_assign(dt::StrView recv_name, Node* expr);
  Node* strict_sum_assign(dt::StrView recv_name, Node* expr);
  Node* strict_if_stmt(Node* cond, NodeList&& on_true, NodeList&& on_false);

# undef Node
# undef NodeList
}
