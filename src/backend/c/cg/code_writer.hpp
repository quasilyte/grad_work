#pragma once

#include "ast/visitor.hpp"
#include "dt/str_view.hpp"
#include "sym/type.hpp"
#include <vector>

namespace ast {
  struct BinaryNode;
}

namespace sym {
  struct NamedFn;
  struct UnnamedFn;
  struct MonoFn;
}

namespace cc {
  struct TranslationUnit;
}

namespace c_cg {
  class CodeWriter;
}

class c_cg::CodeWriter: public ast::Visitor {
public:
  typedef std::vector<ast::Node*> NodeList;

  static void Run(ast::Node*);
  static void RunGroupedList(char delimiter, const NodeList&);
  static void RunButLast(char delimiter, const NodeList&);
  static void RunList(char delimiter, const NodeList&);
  static void RunLambda(sym::UnnamedFn*);
  static void RunFunc(sym::NamedFn*);
  static void RunMonoFn(sym::MonoFn*);
  static void RunBlock(const NodeList&);

  void Visit(ast::Node*) override;
  void Visit(ast::Int*) override;
  void Visit(ast::Real*) override;
  void Visit(ast::Str*) override;
  void Visit(ast::Sum*) override;
  void Visit(ast::SumAssign*) override;
  void Visit(ast::Sub*) override;
  void Visit(ast::Mul*) override;
  void Visit(ast::Div*) override;
  void Visit(ast::NumLt*) override;
  void Visit(ast::NumGt*) override;
  void Visit(ast::NumEq*) override;
  void Visit(ast::SetVar*) override;
  void Visit(ast::SetAttr*) override;
  void Visit(ast::DefVar*) override;
  void Visit(ast::IfExpr*) override;
  void Visit(ast::IfStmt*) override;
  void Visit(ast::IntCase*) override;
  void Visit(ast::Var*) override;
  void Visit(ast::LambdaExpr*) override;
  void Visit(ast::FuncCall*) override;
  void Visit(ast::MonoFnCall*) override;
  void Visit(ast::VarCall*) override;
  void Visit(ast::DynamicCall*) override;
  void Visit(ast::CompoundLit*) override;
  void Visit(ast::AttrAccess*) override;
  void Visit(ast::Intrinsic*) override;
  void Visit(ast::IntrinsicCall1*) override;
  void Visit(ast::Each*) override;
  void Visit(ast::Return*) override;

private:
  void VisitUnary(char op, ast::Node*);

  template<class T>
  void VisitBinary(T op, const ast::BinaryNode&);

  void Call(dt::StrView name, ast::Node* arg);
  void Cast(ast::Node* expr, sym::Type target_ty);
};
