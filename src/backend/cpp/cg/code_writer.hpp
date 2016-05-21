#pragma once

#include "ast/visitor.hpp"
#include "dt/str_view.hpp"
#include "sym/type.hpp"
#include <vector>

namespace cc {
  struct TranslationUnit;
}

namespace cpp_cg {
  class CodeWriter;
  struct FileWriter;
}

class cpp_cg::CodeWriter: public ast::Visitor {
public:
  typedef std::vector<ast::Node*> NodeList;

  static void Run(ast::Node*, const cc::TranslationUnit&, const FileWriter&);

  CodeWriter(const cc::TranslationUnit&, const FileWriter&);

  void Visit(ast::Node*) override;
  void Visit(ast::Int*) override;
  void Visit(ast::Real*) override;
  void Visit(ast::Str*) override;
  void Visit(ast::Sym*) override;
  void Visit(ast::Sum*) override;
  void Visit(ast::Sub*) override;
  void Visit(ast::Mul*) override;
  void Visit(ast::Lt*) override;
  void Visit(ast::Gt*) override;
  void Visit(ast::SetVar*) override;
  void Visit(ast::SetAttr*) override;
  void Visit(ast::DefVar*) override;
  void Visit(ast::If*) override;
  void Visit(ast::Var*) override;
  void Visit(ast::LambdaExpr*) override;
  void Visit(ast::FuncCall*) override;
  void Visit(ast::VarCall*) override;
  void Visit(ast::CompoundLiteral*) override;
  void Visit(ast::AttrAccess*) override;
  void Visit(ast::Intrinsic*) override;
  void Visit(ast::IntrinsicCall1*) override;

private:
  const cc::TranslationUnit& tu;
  const cpp_cg::FileWriter& fw;

  void VisitButLast(char delimiter, const NodeList&);
  void VisitList(char delimiter, const NodeList&);
  void VisitGroupedList(char delimiter, const NodeList&);
  void VisitUnary(char op, ast::Node*);

  void Call(dt::StrView name, ast::Node* arg);
  void Cast(ast::Node* expr, sym::Type target_ty);
};
