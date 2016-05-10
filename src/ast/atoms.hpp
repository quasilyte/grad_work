#pragma once

#include "ast/node.hpp"
#include "lex/token.hpp"
#include "io/file_writer.hpp"

namespace ast {
  struct Int;
  struct Int2;
  struct Real;
  struct Str;
  struct Var;
}

struct ast::Int2: public Node {
  const char* str;
};

struct ast::Int: public Node {
  Int(lex::Token);
  void GenerateCode(const sym::Module*, const io::FileWriter&) override;
  const sym::Type* Type() override;
  lex::Token tok;
};

struct ast::Real: public Node {
  Real(lex::Token);
  void GenerateCode(const sym::Module*, const io::FileWriter&) override;
  const sym::Type* Type() override;
  lex::Token tok;
};

struct ast::Str: public Node {
  Str(lex::Token);
  void GenerateCode(const sym::Module*, const io::FileWriter&) override;
  const sym::Type* Type() override;
  lex::Token tok;
};

struct ast::Var: public Node {
  Var(const dt::StrView* name, const sym::Type* type);
  void GenerateCode(const sym::Module*, const io::FileWriter&) override;
  const sym::Type* Type() override;
  const dt::StrView* name;
  const sym::Type* type;
};
