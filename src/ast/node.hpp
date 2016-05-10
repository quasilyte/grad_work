#pragma once

#include "io/file_writer.hpp"
#include "sym/type.hpp"
#include "sym/module.hpp"

namespace ast {
  class Node;
  class Visitor;
}

class ast::Node {
public:
  virtual void Accept(Visitor*) = 0;
};

