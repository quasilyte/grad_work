#pragma once

namespace ast {
  class Visitor;
  class Node;
  class Int;
  class Real;
  class Str;
  class Sum;
  class SetGlobal;
  class DefLocal;
  struct If;
}

class ast::Visitor {
public:
  virtual void Visit(Node*) = 0;
  virtual void Visit(Int*) = 0;
  virtual void Visit(Real*) = 0;
  virtual void Visit(Str*) = 0;
  virtual void Visit(Sum*) = 0;
  virtual void Visit(SetGlobal*) = 0;
  virtual void Visit(DefLocal*) = 0;
  virtual void Visit(If*) = 0;
};

// 6
//
