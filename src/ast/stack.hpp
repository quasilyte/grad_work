#pragma once

namespace ast {
  class Stack;
  struct Node;
}

class ast::Stack {
public:
  class OverflowError{};

  void push(Node*);
  Node* top() const noexcept;
  Node* pop();

private:
  static const int MAX_SIZE = 16;
  int size = -1;
  Node* nodes[MAX_SIZE];
};
