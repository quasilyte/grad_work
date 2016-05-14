#pragma once

#include "lex/token_stream.hpp"
#include "cc/top_level.hpp"
#include "cc/translation_unit.hpp"
#include "sym/module.hpp"
#include "dt/dict.hpp"
#include <vector>

namespace ast {
  class Node;
}

namespace cc {
  class Parser;
}

class cc::Parser {
public:

  static TranslationUnit Run(const TopLevel&);

private:
  const int LONGEST_ARG_LIST = 32;

  sym::Module module;
  const TopLevel& top;
  TranslationUnit result;

  Parser(const TopLevel&);

  TranslationUnit Parse();

  void ParseGlobal(lex::TokenStream&);
  void ParseExpr(lex::Token& tok);

  ast::Node* ParseToken(lex::Token);
  ast::Node* ParseList(lex::Token);

  ast::Node* ParseSum(lex::TokenStream&);
  ast::Node* ParseSet(lex::TokenStream&);
  ast::Node* ParseDefLocal(lex::TokenStream&);
  ast::Node* ParseIf(lex::TokenStream&);

  /*

  void ParseFuncDecls();

  void ExecDirective(lex::Token);
  void ExecDef(lex::TokenStream);

  ast::Node* ParseToken(lex::Token);
  ast::Node* ParseList(lex::Token);

  ast::Node* ParseFuncCall(lex::Token name, lex::TokenStream args);
  ast::Node* ParseIf(lex::TokenStream);
  ast::Node* ParseDef(lex::TokenStream);
  ast::Node* ParseSet(lex::TokenStream);
  ast::Node* ParseSum(lex::TokenStream);
  */
};
