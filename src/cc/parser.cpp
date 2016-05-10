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

TranslationUnit Parser::Run(const TopLevel& top) {
  Parser self{top};
  return self.Parse();
}

Parser::Parser(const TopLevel& top):
module{"global"}, top{top} {}

TranslationUnit Parser::Parse() {
  // (#def |x 1)
  for (lex::TokenStream global : top.globals) {
    ParseGlobal(global);
  }

  return result;
}

lex::Token next(TokenStream& ts, enum Token::Tag tag, const char* msg) {
  auto token = ts.NextToken();
  if (token.Is(tag)) {
    return token;
  } else {
    throw msg;
  }
}

void Parser::ParseGlobal(TokenStream& args) {
  // auto name_tok = next(args, Token::INT, "=)");

  auto name_tok = args.NextToken();
  auto expr_tok = args.NextToken();

  // result.exprs.push_back();
}

/*
Node* Parser::ParseToken(Token tok) {
  switch (tok.Tag()) {
  case Token::INT:
    return new Int{tok};
  case Token::REAL:
    return new Real{tok};
  case Token::STR:
    return new Str{tok};
  case Token::WORD: {
    auto local = module.Local(tok.AsStrView());
    return new Var{local.bound_name, local.type};
  }
  case Token::LIST:
    return ParseList(tok);

  default:
    throw "not implemented";
  }
}*/

/*

  LEGACY

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

// (def (f a) x)
Node* Parser::ParseDef(TokenStream toks) {
  auto args = eval_tokens(toks, 2);
  auto expr = ParseToken(args[1]);

  if (args[0].IsList()) {
    auto signature = eval_tokens(args[0], 1, 10);
    auto name = signature[0];
    std::vector<Token> params{signature.begin() + 1, signature.end()};
    module.DefineFunc(name.AsStrView(), params.size());
    auto result = new DefFunc{name, std::move(params), expr};
    return result;
  } else if (args[0].IsWord()) {
    auto name = module.DefineLocal(args[0].AsStrView(), expr->Type());
    // return new DefVar{args[0].AsStrView(), expr};
    return new DefLocal{name, expr};
  } else {
    throw "unknown def form";
  }
}
#include <cstdio>
Node* Parser::ParseSet(TokenStream toks) {
  auto args = eval_tokens(toks, 2);
  auto expr = ParseToken(args[1]);



  // module.MergeSymbol(args[0].AsStrView(), expr->Type());
  auto name = module.RebindLocal(args[0].AsStrView(), expr->Type());
  return new DefLocal{name, expr};
  // return new Set{args[0], expr};
}

Node* Parser::ParseFuncCall(lex::Token name, TokenStream args) {
  auto parsed_args = eval_tokens(args, 1, 10);
  // auto& symbol = module.Func(args[0].AsStrView());

  std::vector<Node*> xs;
  xs.reserve(parsed_args.size());
  for (auto arg : parsed_args) {
    xs.push_back(ParseToken(arg));
  }

  return new FuncCall{&sym::Type::INT, name, std::move(xs)};
}

Node* Parser::ParseSum(TokenStream toks) {
  auto args = eval_tokens(toks, 1, 5);

  std::vector<Node*> operands;
  operands.reserve(args.size());
  for (auto arg : args) {
    operands.push_back(ParseToken(arg));
  }

  return new Sum{std::move(operands)};
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
    case encode9("def"): return ParseDef(list);
    case encode9("set!"): return ParseSet(list);
    case encode9("+"): return ParseSum(list);

    default:
      return ParseFuncCall(head, list);
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
  case Token::WORD: {
    auto local = module.Local(tok.AsStrView());
    return new Var{local.bound_name, local.type};
  }
  case Token::LIST:
    return ParseList(tok);

  default:
    throw "not implemented";
  }
}
*/
