#pragma once

#include "ast/node.hpp"
#include "lex/token.hpp"
#include <vector>

namespace ast {
  struct DefVar;
  struct DefLocal;
  struct DefFunc;
  struct Set;
}

struct ast::DefVar: public Node {
  DefVar(dt::StrView name, Node* assignment);
  void GenerateCode(const sym::Module&, const io::FileWriter&) override;
  dt::StrView name;
  Node* assignment;
};

struct ast::DefLocal: public Node {
  DefLocal(const dt::StrView* name, Node* assignment);
  void GenerateCode(const sym::Module&, const io::FileWriter&) override;
  const dt::StrView* name;
  Node* assignment;
};

struct ast::DefFunc: public Node {
  DefFunc(lex::Token name, std::vector<lex::Token>&& params, Node* body);
  void GenerateCode(const sym::Module&, const io::FileWriter&) override;
  lex::Token name;
  std::vector<lex::Token> params;
  Node* body;
  // std::vector<Node*> body;
};

struct ast::Set: public Node {
  Set(lex::Token name, Node* assignment);
  void GenerateCode(const sym::Module&, const io::FileWriter&) override;
  lex::Token name;
  Node* assignment;
};
