#pragma once

#include "lex/token_stream.hpp"
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

private:
  Tree tree;
  lex::TokenStream toks;

  ast::Node* ParseToken(lex::Token);
  ast::Node* ParseList(lex::Token);

  ast::Node* ParseIf(lex::TokenStream);
  ast::Node* ParseDefine(lex::TokenStream);
  ast::Node* ParseSet(lex::TokenStream);
  ast::Node* ParseSum(lex::TokenStream);
};
