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

  while (!toks.next_token().is_eof()) {
    if (items.size() == max_count) {
      throw "too much args!";
    }
    items.push_back(toks.current_token());
  }

  if (items.size() < min_count) {
    throw "too few args!";
  }

  return items;
}

std::vector<Token> eval_tokens(TokenStream toks, int count) {
  return eval_tokens(toks, count, count);
}

Node* Parser::parse_define(TokenStream toks) {
  auto args = eval_tokens(toks, 2);
  auto result = new Define{
    args[0],
    parse_token(args[1]),
  };
  return result;
}

Node* Parser::parse_set(TokenStream toks) {
  auto args = eval_tokens(toks, 2);
  auto result = new Set{
    args[0],
    parse_token(args[1]),
  };
  return result;
}

Node* Parser::parse_sum(TokenStream toks) {
  /*
  auto args = eval_tokens(toks, 1, 5);
  auto result = new Sum{args};
  return result;
  */
}

Node* Parser::parse_if(TokenStream toks) {
  auto args = eval_tokens(toks, 3);
  auto result = new If{
    parse_token(args[0]),
    parse_token(args[1]),
    parse_token(args[2]),
  };
  return result;
}

Node* Parser::parse_list(Token tok) {
  using namespace mn_hash;

  TokenStream list{tok};
  if (list.next_token().is_word()) {
    auto head = list.current_token();
    auto word_hash = encode9(head.get_val(), head.get_len());

    switch (word_hash) {
    case encode9("if"): return parse_if(list);
    case encode9("define"): return parse_define(list);
    case encode9("set!"): return parse_set(list);
    case encode9("+"): return parse_sum(list);

    default:
      throw "cant parse user function yet";
    }

  } else {
    throw "car(list) != symbol";
  }
}

Node* Parser::parse_token(Token tok) {
  switch (tok.get_tag()) {
  case Token::INT:
    return new Int{tok};
  case Token::REAL:
    return new Real{tok};
  case Token::LIST:
    return parse_list(tok);

  default:
    throw "not implemented";
  }
}

const Parser::Tree& Parser::parse() {
  while (!toks.next_token().is_eof()) {
    tree.push_back(parse_token(toks.current_token()));
  }

  return tree;
}
