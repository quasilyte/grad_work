#pragma once

#include "ast/node.hpp"
#include "lex/token.hpp"

namespace ast {
  struct Define;
  struct Set;
}

struct ast::Define: public Node {
  Define(lex::Token, Node*);
  void GenerateCode(const sym::Module&, const io::FileWriter&) override;
  lex::Token name;
  Node* assignment;
};

struct ast::Set: public Node {
  Set(lex::Token, Node*);
  void GenerateCode(const sym::Module&, const io::FileWriter&) override;
  lex::Token name;
  Node* assignment;
};
