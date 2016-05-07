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

  const Tree& parse();

private:
  Tree tree;
  lex::TokenStream toks;

  ast::Node* parse_token(lex::Token);
  ast::Node* parse_list(lex::Token);

  ast::Node* parse_if(lex::TokenStream);
  ast::Node* parse_define(lex::TokenStream);
  ast::Node* parse_set(lex::TokenStream);
  ast::Node* parse_sum(lex::TokenStream);
};
