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
  Int(lex::Token);
  void GenerateCode(const sym::Module&, const io::FileWriter&) override;
  const sym::Type& Type();
  lex::Token tok;
};

struct ast::Real: public Node {
  Real(lex::Token);
  void GenerateCode(const sym::Module&, const io::FileWriter&) override;
  const sym::Type& Type();
  lex::Token tok;
};

struct ast::Str: public Node {
  Str(lex::Token);
  void GenerateCode(const sym::Module&, const io::FileWriter&) override;
  const sym::Type& Type();
  lex::Token tok;
};
