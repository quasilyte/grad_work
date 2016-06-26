#pragma once

namespace ast {
  class Visitor;
  struct Node;
  struct Int;
  struct Real;
  struct Str;
  struct Sum;
  struct Sub;
  struct Mul;
  struct Div;
  struct NumEq;
  struct NumLt;
  struct NumGt;
  struct SetVar;
  struct SetAttr;
  struct DefVar;
  struct IfExpr;
  struct IntCase;
  struct Var;
  struct LambdaExpr;
  struct FuncCall;
  struct MonoFnCall;
  struct VarCall;
  struct DynamicCall;
  struct CompoundLit;
  struct AttrAccess;
  struct Intrinsic;
  struct IntrinsicCall1;
  struct Each;
  struct Return;
  // Statements:
  struct Assign;
  struct SumAssign;
  struct IfStmt;
}

class ast::Visitor {
public:
  virtual void Visit(Node*) = 0;
  virtual void Visit(Int*) = 0;
  virtual void Visit(Real*) = 0;
  virtual void Visit(Str*) = 0;
  virtual void Visit(Sum*) = 0;
  virtual void Visit(Mul*) = 0;
  virtual void Visit(Div*) = 0;
  virtual void Visit(NumLt*) = 0;
  virtual void Visit(NumGt*) = 0;
  virtual void Visit(NumEq*) = 0;
  virtual void Visit(Sub*) = 0;
  virtual void Visit(SetVar*) = 0;
  virtual void Visit(SetAttr*) = 0;
  virtual void Visit(DefVar*) = 0;
  virtual void Visit(IfExpr*) = 0;
  virtual void Visit(IntCase*) = 0;
  virtual void Visit(Var*) = 0;
  virtual void Visit(LambdaExpr*) = 0;
  virtual void Visit(FuncCall*) = 0;
  virtual void Visit(MonoFnCall*) = 0;
  virtual void Visit(VarCall*) = 0;
  virtual void Visit(DynamicCall*) = 0;
  virtual void Visit(CompoundLit*) = 0;
  virtual void Visit(AttrAccess*) = 0;
  virtual void Visit(Intrinsic*) = 0;
  virtual void Visit(IntrinsicCall1*) = 0;
  virtual void Visit(Each*) = 0;
  virtual void Visit(Return*) = 0;
  // Statements:
  virtual void Visit(Assign*) = 0;
  virtual void Visit(SumAssign*) = 0;
  virtual void Visit(IfStmt*) = 0;
};

