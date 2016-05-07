#include "cc/parser.hpp"

#include "mn_hash.hpp"
#include "ast/cond.hpp"
#include "ast/atoms.hpp"
#include "ast/defs.hpp"
#include <cstring>
#include <vector>

#include "dbg/lex.hpp"

using namespace cc;
using namespace lex;
using namespace ast;

Parser::Parser(const char *input):
toks{TokenStream{input, strlen(input)}} {}

std::vector<Token> eval_tokens(TokenStream toks, int min_count, int max_count) {
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

Node* Parser::ParseDefine(TokenStream toks) {
  auto args = eval_tokens(toks, 2);
  auto result = new Define{
    args[0],
    ParseToken(args[1]),
  };
  return result;
}

Node* Parser::ParseSet(TokenStream toks) {
  auto args = eval_tokens(toks, 2);
  auto result = new Set{
    args[0],
    ParseToken(args[1]),
  };
  return result;
}

Node* Parser::ParseSum(TokenStream toks) {
  /*
  auto args = eval_tokens(toks, 1, 5);
  auto result = new Sum{args};
  return result;
  */
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
    case encode9("define"): return ParseDefine(list);
    case encode9("set!"): return ParseSet(list);
    case encode9("+"): return ParseSum(list);

    default:
      throw "cant parse user function yet";
    }

  } else {
    throw "car(list) != symbol";
  }
}

Node* Parser::ParseToken(Token tok) {
  switch (tok.Tag()) {
  case Token::INT:
    return new Int{tok};
  case Token::REAL:
    return new Real{tok};
  case Token::LIST:
    return ParseList(tok);

  default:
    throw "not implemented";
  }
}

const Parser::Tree& Parser::Parse() {
  while (!toks.NextToken().IsEof()) {
    tree.push_back(ParseToken(toks.CurrentToken()));
  }

  return tree;
}
