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
  static const int RT_TYPE = 0;
  Int(lex::Token);
  void generate_code(io::FileWriter*);
  const char* get_type_name() const;
  lex::Token tok;
};

struct ast::Real: public Node {
  static const int RT_TYPE = 1;
  Real(lex::Token);
  void generate_code(io::FileWriter*);
  const char* get_type_name() const;
  lex::Token tok;
};
