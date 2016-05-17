#pragma once

namespace ast {
  struct Node;
  class Visitor;
}

struct ast::Node {
  virtual void Accept(Visitor*) = 0;
};

