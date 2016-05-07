#include "ast/node.hpp"

using namespace ast;

Node::Node(): type{sym::Type{0, "void", sym::Type::VOID}} {}

Node::Node(sym::Type type): type{type} {}

const sym::Type& Node::Type() const noexcept {
  return type;
}
