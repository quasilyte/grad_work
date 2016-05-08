#pragma once

#include "ast/node.hpp"
#include "lex/token.hpp"

namespace ast {
  struct Def;
  struct Set;
}

struct ast::Def: public Node {
  Def(lex::Token, Node*);
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
