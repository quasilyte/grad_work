#include "cc/parser.hpp"

#include "mn_hash.hpp"
#include "ast/cond.hpp"
#include "ast/atoms.hpp"
#include "ast/defs.hpp"
#include "ast/builtins.hpp"
#include "dt/str_view.hpp"
#include "dbg/lex.hpp"
#include "dbg/dt.hpp"
#include <cstring>
#include <vector>

#include "dbg/lex.hpp"

using namespace cc;
using namespace lex;
using namespace ast;
using namespace dt;

Parser::Parser(const char *input):
module{"global"}, toks{TokenStream{input, strlen(input)}} {}

std::vector<Token> eval_tokens(TokenStream toks, uint min_count, uint max_count) {
  std::vector<Token> items;
  items.reserve(min_count);

  while (!toks.NextToken().IsEof()) {
    if (items.size() == max_count) {
      throw "too much args!";
    }
    items.push_back(toks.CurrentToken());
  }

  if (items.size() < min_count) {
    throw "too few args!";
  }

  return items;
}

std::vector<Token> eval_tokens(TokenStream toks, int count) {
  return eval_tokens(toks, count, count);
}

Node* Parser::ParseLet(TokenStream toks) {
  auto args = eval_tokens(toks, 2);
  auto expr = ParseToken(args[1]);
  auto result = new Let{args[0], expr};

  module.DefineSymbol(args[0].AsStrView(), expr->Type());

  return result;
}

Node* Parser::ParseSet(TokenStream toks) {
  auto args = eval_tokens(toks, 2);
  auto& symbol = module.SymbolMut(args[0].AsStrView());

  if (symbol.Defined()) {
    auto expr = ParseToken(args[1]);
    symbol = symbol.Merge(expr->Type());
    return new Set{args[0], expr};
  } else {
    throw "set of undefined";
  }
}

Node* Parser::ParseSum(TokenStream toks) {
  auto args = eval_tokens(toks, 1, 5);

  std::vector<Node*> operands;
  operands.reserve(args.size());
  for (auto arg : args) {
    operands.push_back(ParseToken(arg));
  }

  return new Sum{operands};
}

Node* Parser::ParseIf(TokenStream toks) {
  auto args = eval_tokens(toks, 3);
  auto result = new If{
    ParseToken(args[0]),
    ParseToken(args[1]),
    ParseToken(args[2]),
  };
  return result;
}

Node* Parser::ParseList(Token tok) {
  using namespace mn_hash;

  TokenStream list{tok};
  if (list.NextToken().IsWord()) {
    auto head = list.CurrentToken();
    auto word_hash = encode9(head.Val(), head.Len());

    switch (word_hash) {
    case encode9("if"): return ParseIf(list);
    case encode9("let"): return ParseLet(list);
    case encode9("set!"): return ParseSet(list);
    case encode9("+"): return ParseSum(list);

    default:
      throw "cant parse user function yet";
    }

  } else {
    throw "car(list) != symbol";
  }
}

void Parser::ExecDirective(Token tok) {
  using namespace mn_hash;

  TokenStream list{tok};

  auto head = list.NextToken();
  auto word_hash = encode9(head.Val() + 1, head.Len() - 1);

  switch (word_hash) {
  case encode9(";"): return;

  default:
    throw "unknown directive";
  }
}

Node* Parser::ParseToken(Token tok) {
  switch (tok.Tag()) {
  case Token::INT:
    return new Int{tok};
  case Token::REAL:
    return new Real{tok};
  case Token::STR:
    return new Str{tok};
  case Token::WORD:
    return new Var{module.Symbol(tok.AsStrView()), tok};
  case Token::LIST:
    return ParseList(tok);

  default:
    throw "not implemented";
  }
}

const Parser::Tree& Parser::Parse() {
  while (!toks.NextToken().IsEof()) {
    auto tok = toks.CurrentToken();

    if ('#' == *tok.Val() && tok.IsList()) {
      ExecDirective(tok);
    } else {
      tree.push_back(ParseToken(tok));
    }
  }

  return tree;
}

const sym::Module& Parser::Module() const noexcept {
  return module;
}
