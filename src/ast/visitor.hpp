#pragma once

namespace ast {
  class Visitor;
  struct Node;
  struct Int;
  struct Real;
  struct Str;
  struct Sym;
  struct Sum;
  struct SetVar;
  struct DefVar;
  struct If;
  struct Var;
  struct FuncCall;
  struct CompoundLiteral;
}

class ast::Visitor {
public:
  virtual void Visit(Node*) = 0;
  virtual void Visit(Int*) = 0;
  virtual void Visit(Real*) = 0;
  virtual void Visit(Str*) = 0;
  virtual void Visit(Sym*) = 0;
  virtual void Visit(Sum*) = 0;
  virtual void Visit(SetVar*) = 0;
  virtual void Visit(DefVar*) = 0;
  virtual void Visit(If*) = 0;
  virtual void Visit(Var*) = 0;
  virtual void Visit(FuncCall*) = 0;
  virtual void Visit(CompoundLiteral*) = 0;
};

