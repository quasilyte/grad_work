#pragma once

#include "ast/visitor.hpp"
#include "sym/type.hpp"

namespace cc {
  class TypeDeducer;
}

class cc::TypeDeducer: public ast::Visitor {
public:
  static sym::Type Run(ast::Node*);

  void Visit(ast::Node*) override;
  void Visit(ast::Int*) override;
  void Visit(ast::Real*) override;
  void Visit(ast::Str*) override;
  void Visit(ast::Sym*) override;
  void Visit(ast::Sum*) override;
  void Visit(ast::Mul*) override;
  void Visit(ast::Lt*) override;
  void Visit(ast::Gt*) override;
  void Visit(ast::Sub*) override;
  void Visit(ast::SetVar*) override;
  void Visit(ast::SetAttr*) override;
  void Visit(ast::DefVar*) override;
  void Visit(ast::If*) override;
  void Visit(ast::Var*) override;
  void Visit(ast::FuncCall*) override;
  void Visit(ast::CompoundLiteral*) override;
  void Visit(ast::AttrAccess*) override;
  void Visit(ast::TypeCast*) override;

private:
  sym::Type result;
};
