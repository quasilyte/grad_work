#pragma once

#include "ast/visitor.hpp"

namespace io {
  class FileWriter;
}

namespace cpp_cg {
  class Visitor;
}

class cpp_cg::Visitor: public ast::Visitor {
public:
  static void Run(ast::Node*, const io::FileWriter&);

  Visitor(const io::FileWriter&);

  void Visit(ast::Node*) override;
  void Visit(ast::Int*) override;
  void Visit(ast::Real*) override;
  void Visit(ast::Str*) override;
  void Visit(ast::Sum*) override;
  void Visit(ast::SetGlobal*) override;
  void Visit(ast::DefLocal*) override;
  void Visit(ast::If*) override;

private:
  const io::FileWriter& fw;
};
