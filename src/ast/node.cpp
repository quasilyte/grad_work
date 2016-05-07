#include "ast/node.hpp"

using namespace ast;

Node::Node(): type{sym::Type{0, "void", sym::Type::VOID}} {}

Node::Node(sym::Type type): type{type} {}

const sym::Type& Node::get_type() const noexcept {
  return type;
}
