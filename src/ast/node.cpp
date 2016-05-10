#include "ast/node.hpp"

using namespace ast;

const sym::Type* Node::Type() {
  return &sym::Type::VOID;
}

