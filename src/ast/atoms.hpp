#pragma once

#include "ast/node.hpp"
#include "lex/token.hpp"
#include "io/file_writer.hpp"

namespace ast {
  struct Int;
  struct Real;
  struct Str;
}

struct ast::Int: public Node {
  static sym::Type RT_TYPE;
  Int(lex::Token);
  void GenerateCode(const io::FileWriter&) override;
  lex::Token tok;
};

struct ast::Real: public Node {
  static sym::Type RT_TYPE;
  Real(lex::Token);
  void GenerateCode(const io::FileWriter&) override;
  lex::Token tok;
};
