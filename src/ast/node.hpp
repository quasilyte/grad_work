#pragma once

#include "sym/type.hpp"

namespace ast {
  struct Node;
  class Visitor;
}

struct ast::Node {
  virtual void Accept(Visitor*) = 0;
  virtual sym::Type Type() = 0;
  virtual const char* Symbol();
};

