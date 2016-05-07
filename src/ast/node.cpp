#include "ast/node.hpp"

using namespace ast;

Node::Node() {}

Node::Node(sym::Type type): type{type} {}

const sym::Type& Node::Type() const noexcept {
  return type;
}
