#include "ast/stack.hpp"

using namespace ast;

void Stack::push(Node* node) {
  if (++size == MAX_SIZE) {
    throw OverflowError{};
  }

  nodes[size] = node;
}

Node* Stack::top() const noexcept {
  return nodes[size];
}

Node* Stack::pop() {
  return nodes[size--];
}
