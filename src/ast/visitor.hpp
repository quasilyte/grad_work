#pragma once

namespace ast {
  class Visitor;
  struct Node;
  struct Int;
  struct Real;
  struct Str;
  struct Sym;
  struct Sum;
  struct Sub;
  struct Mul;
  struct Eq;
  struct Lt;
  struct Gt;
  struct SetVar;
  struct SetAttr;
  struct DefVar;
  struct If;
  struct Var;
  struct FuncCall;
  struct CompoundLiteral;
  struct AttrAccess;
  struct TypeCast;
  struct Intrinsic;
}

class ast::Visitor {
public:
  virtual void Visit(Node*) = 0;
  virtual void Visit(Int*) = 0;
  virtual void Visit(Real*) = 0;
  virtual void Visit(Str*) = 0;
  virtual void Visit(Sym*) = 0;
  virtual void Visit(Sum*) = 0;
  virtual void Visit(Mul*) = 0;
  virtual void Visit(Lt*) = 0;
  virtual void Visit(Gt*) = 0;
  virtual void Visit(Sub*) = 0;
  virtual void Visit(SetVar*) = 0;
  virtual void Visit(SetAttr*) = 0;
  virtual void Visit(DefVar*) = 0;
  virtual void Visit(If*) = 0;
  virtual void Visit(Var*) = 0;
  virtual void Visit(FuncCall*) = 0;
  virtual void Visit(CompoundLiteral*) = 0;
  virtual void Visit(AttrAccess*) = 0;
  virtual void Visit(TypeCast*) = 0;
  virtual void Visit(Intrinsic*) = 0;
};

