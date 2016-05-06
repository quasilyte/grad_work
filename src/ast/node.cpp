#include "ast/node.hpp"

using namespace ast;

Node::Node(int type): type{type} {}

int Node::get_type() const noexcept {
  return type;
}

const char* Node::get_type_name() const {
  return "void";
}
