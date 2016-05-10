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
  void Visit(ast::Sum*) override;
  void Visit(ast::SetGlobal*) override;
  void Visit(ast::DefLocal*) override;

private:
  sym::Type result;
};
