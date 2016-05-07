#pragma once

#include "lex/token_stream.hpp"
#include "sym/module.hpp"
#include "dt/dict.hpp"
#include <vector>

namespace ast {
  struct Node;
}

namespace cc {
  class Parser;
}

class cc::Parser {
public:
  typedef std::vector<ast::Node*> Tree;

  Parser(const char* input);

  const Tree& Parse();
  const sym::Module& Module() const noexcept;

private:
  Tree tree;
  sym::Module module;
  lex::TokenStream toks;

  void ExecDirective(lex::Token);

  void ExecType(lex::TokenStream);

  ast::Node* ParseToken(lex::Token);
  ast::Node* ParseList(lex::Token);

  ast::Node* ParseIf(lex::TokenStream);
  ast::Node* ParseDefine(lex::TokenStream);
  ast::Node* ParseSet(lex::TokenStream);
  ast::Node* ParseSum(lex::TokenStream);
};
