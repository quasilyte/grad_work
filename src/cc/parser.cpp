#include "cc/parser.hpp"

#include "mn_hash.hpp"
#include "ast/cond.hpp"
#include "ast/atoms.hpp"
#include "ast/defs.hpp"
#include "ast/builtins.hpp"
#include "dt/str_view.hpp"
#include "dbg/lex.hpp"
#include "dbg/dt.hpp"
#include "dbg/sym.hpp"
#include "cc/type_deducer.hpp"
#include "echo.hpp"
#include <tuple>
#include <cstring>
#include <vector>
#include "intrinsic/overloadings.hpp"
#include "intrinsic/type_ops.hpp"

#include "dbg/lex.hpp"

using namespace cc;
using namespace lex;
using namespace ast;
using namespace dt;
using namespace sym;

bool is_type_name(dt::StrView maybe_type_name) {
  return maybe_type_name[0] >= 'A'
      && maybe_type_name[0] <= 'Z';
}

int param_seq_len(lex::TokenStream toks) {
  int result = 0;

  while (!toks.NextToken().IsEof()
         && !is_type_name(toks.CurrentToken())) {
    result += 1;
  }

  return result;
}

int length(TokenStream toks) {
  int size = 0;

  while (!toks.NextToken().IsEof()) {
    size += 1;
  }

  return size;
}

std::vector<Token> eval_tokens(TokenStream& toks, uint min_count, uint max_count) {
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

sym::Type Parser::TypeByName(dt::StrView name) const {
  using namespace mn_hash;

  switch (encode9(name.Data(), name.Len())) {
  case encode9("Int"): return Type::Int();
  case encode9("Real"): return Type::Real();
  case encode9("Num"): return Type::Num();
  case encode9("Any"): return Type::Any();
  case encode9("Str"): return Type::Str();

  default:
    auto type_info = module.Struct(name);
    if (type_info) {
      return type_info->type;
    } else {
      throw "TypeByName: unknown type";
    }
  }
}

TranslationUnit Parser::Run(const TopLevel& top) {
  Parser self{top};
  auto tu = self.Parse();
  tu.module = self.module; // #FIXME: is this causes whole module to copy?

  return tu;
}

Parser::Parser(const TopLevel& top): top{top} {}

TranslationUnit Parser::Parse() {
  for (lex::TokenStream s : top.structs) {
    ParseDefStruct(s);
  }

  for (lex::TokenStream global : top.globals) {
    ParseGlobal(global);
  }

  for (lex::TokenStream func : top.funcs) {
    ParseSignature(func);
  }

  for (lex::Token expr : top.exprs) {
    ParseExpr(expr);
  }

  return result;
}

void Parser::ParseDefStruct(TokenStream& toks) {
  dt::StrView name = toks.NextToken();
  std::vector<sym::Param> attrs;

  while (!toks.NextToken().IsEof()) {
    auto tok = toks.CurrentToken();

    if (tok.IsList()) {
      lex::TokenStream typed_list{tok};
      auto type = TypeByName(typed_list.NextToken());

      while (!typed_list.NextToken().IsEof()) {
        attrs.push_back(Param{typed_list.CurrentToken(), type});
      }
    } else {
      attrs.push_back(Param{tok, Type::Any()});
    }
  }

  module.DefineStruct(name, std::move(attrs));
  result.structs.push_back(name);
}

Node* Parser::ParseVar(TokenStream& toks) {
  StrView name;
  Node* expr;
  Type ty;

  std::tie(name, expr, ty) = FetchVarInfo(toks);

  module.DefineLocal(name, ty);
  return new DefVar{name, expr, ty};
}

void Parser::ParseGlobal(TokenStream& toks) {
  StrView name;
  Node* expr;
  Type ty;

  std::tie(name, expr, ty) = FetchVarInfo(toks);

  result.globals.push_back(new DefVar{name, expr, ty});
  module.DefineGlobalSymbol(name, ty);
}

void Parser::ParseExpr(Token& tok) {
  if (tok.IsList()) {
    result.exprs.push_back(ParseList(tok));
  } else {
    result.exprs.push_back(ParseToken(tok));
  }
}

Node* Parser::ParseLambdaExpr(TokenStream& toks) {
  lex::TokenStream signature{toks.NextToken()};
  std::vector<sym::Param> params = CollectParams(signature);

  module.CreateScopeLevel();

  for (const sym::Param& param : params) {
    module.DefineLocal(param.name, param.type);
  }

  auto lambda_id = Type::LambdaTag(result.lambdas.size());
  auto lambda_expr = new Lambda{lambda_id, std::move(params), Type::Unknown()};
  auto exprs = CollectParsed(toks);
  auto ty = TypeDeducer::Run(exprs.back());

  module.DropScopeLevel();
  lambda_expr->Define(std::move(exprs), ty);
  result.lambdas.push_back(lambda_expr);

  return new LambdaExpr{lambda_id};
}

void Parser::ParseSignature(TokenStream& toks) {
  lex::TokenStream signature{toks.NextToken()};
  MultiFunc::Key sig_matcher;

  auto name = signature.NextToken();
  auto params = CollectParams(signature);

  module.CreateScopeLevel();

  for (const sym::Param& param : params) {
    sig_matcher.push_back(param.type);
    module.DefineLocal(param.name, param.type);
  }

  auto func = new sym::Func{name, std::move(params), Type::Unknown()};
  module.DeclareFunc(name, sig_matcher, func);

  auto exprs = CollectParsed(toks);
  auto ty = TypeDeducer::Run(exprs.back());
  module.DropScopeLevel();

  func->Define(std::move(exprs), ty);
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
    return ParseWord(tok);
  case Token::LIST:
    return ParseList(tok);

  default:
    throw "parse token: not implemented";
  }
}

Node* Parser::ParseList(Token tok) {
  using namespace mn_hash;

  TokenStream list{tok};

  if (list.NextToken().IsWord()) {
    auto name_tok = list.CurrentToken();
    auto name_hash = encode9(name_tok.Data(), name_tok.Len());

    switch (name_hash) {
    case encode9("fn"): return ParseLambdaExpr(list);
    case encode9("<"): return ParseLt(list);
    case encode9(">"): return ParseGt(list);
    case encode9("+"): return ParseSum(list);
    case encode9("-"): return ParseSub(list);
    case encode9("*"): return ParseMul(list);
    case encode9("set!"): return ParseSet(list);
    case encode9("var"): return ParseVar(list);
    case encode9("if"): return ParseIf(list);
    case encode9("struct"): return ParseStruct(list);
    case encode9("'"): return ParseQuote(list);
    case encode9("get"): return ParseGet(list);
    case encode9("."): return ParseAttrAccess(list);
    case encode9("int"): return ParseIntrinsicCall1(list, intrinsic::int_overloading);
    case encode9("real"): return ParseIntrinsicCall1(list, intrinsic::real_overloading);
    case encode9("num"): return ParseIntrinsicCall1(list, intrinsic::num_overloading);

    default:
      return ParseFuncCall(name_tok, list);
    }

  } else {
    throw "car(list) != symbol";
  }
}

ast::Node* Parser::ParseWord(Token word) {
  using namespace mn_hash;

  auto word_hash = encode9(word.Data(), word.Len());

  switch (word_hash) {
  case encode9("num"): return new Intrinsic{Type::ANY_TO_NUM};
  case encode9("real"): return new Intrinsic{Type::ANY_TO_REAL};
  case encode9("int"): return new Intrinsic{Type::ANY_TO_INT};

  default:
    return new Var{word, module.SymbolOrFunc(word)};
  }
}

ast::Node* Parser::ParseFuncCall(lex::Token& name, lex::TokenStream& args) {
  sym::MultiFunc* multifunc = module.MultiFunc(name);

  if (multifunc) {
    std::vector<Node*> nodes;
    MultiFunc::Key sig_matcher;

    while (!args.NextToken().IsEof()) {
      auto node = ParseToken(args.CurrentToken());
      sig_matcher.push_back(TypeDeducer::Run(node));
      nodes.push_back(node);
    }

    auto func = multifunc->Func(sig_matcher);

    if (func) {
      return new FuncCall{func, std::move(nodes)};
    } else {
      throw "FuncCall: no signature matched arguments";
    }
  } else {
    auto callable = module.Symbol(name);

    if (callable.IsAny()) {
      throw "FuncCall: polymorphic call is not supported yet";
    } else if (callable.IsFunc()) {
      auto func = module.Func(callable.Tag());
      return new VarCall{name, func, std::move(CollectParsed(args))};
    } else {
      throw "FuncCall: called something that can not be called";
    }
  }
}

Node* Parser::ParseSum(TokenStream& toks) {
  return new Sum{std::move(CollectParsed(toks))};
}

Node* Parser::ParseSub(TokenStream& toks) {
  return new Sub{std::move(CollectParsed(toks))};
}

Node* Parser::ParseMul(TokenStream& toks) {
  return new Mul{std::move(CollectParsed(toks))};
}

Node* Parser::ParseLt(TokenStream& toks) {
  return new Lt{std::move(CollectParsed(toks))};
}

Node* Parser::ParseGt(TokenStream& toks) {
  return new Gt{std::move(CollectParsed(toks))};
}

// (set! obj val)
// (set! obj attr val)
Node* Parser::ParseSet(TokenStream& toks) {  
  switch (length(toks)) {
  case 2: {
    auto name = toks.NextToken();
    auto expr = ParseToken(toks.NextToken());
    auto var = module.Symbol(name);

    if (var.CompatibleWith(TypeDeducer::Run(expr))) {
      return new SetVar{name, expr};
    } else {
      throw "set: incompatible types";
    }
  }
  case 3: {
    auto obj_name = toks.NextToken();
    auto attr_name = toks.NextToken();
    auto expr = ParseToken(toks.NextToken());
    auto var = module.Symbol(obj_name);
    auto attr = module.Struct(var.Tag())->Attr(attr_name);

    return new SetAttr{obj_name, attr, expr};
  }
  default:
    throw "set! invalid number of arguments";
  }
}

Node* Parser::ParseIf(TokenStream& toks) {
  auto cond = ParseToken(toks.NextToken());
  auto on_true = ParseToken(toks.NextToken());
  auto on_false = ParseToken(toks.NextToken());

  return new If{cond, on_true, on_false};
}

Node* Parser::ParseStruct(TokenStream& toks) {
  auto s = module.Struct(toks.NextToken());

  if (s) {
    std::vector<Node*> initializers;
    while (!toks.NextToken().IsEof()) {
      initializers.push_back(ParseToken(toks.CurrentToken()));
    }

    return new CompoundLiteral{std::move(initializers), s->type};
  } else {
    throw "type not exist";
  }
}

Node* Parser::ParseGet(TokenStream& toks) {
  dt::StrView obj_name = toks.NextToken();
  auto var = module.Symbol(obj_name);
  auto key = ParseToken(toks.NextToken());
  auto key_ty = TypeDeducer::Run(key);

  if (key_ty.IsSym()) {
    auto attr = module.Struct(var.Tag())->Attr(static_cast<Sym*>(key)->datum);
    return new AttrAccess{obj_name, attr};
  } else {
    throw "dynamic lookup is not supported yet";
  }
}

Node* Parser::ParseQuote(TokenStream& toks) {
  auto quotation = toks.NextToken();

  if (!toks.NextToken().IsEof()) {
    throw "can quote only 1 form";
  }

  switch (quotation.Tag()) {
  case Token::INT:
  case Token::REAL:
  case Token::STR:
    return ParseToken(quotation);
  case Token::WORD:
    return new ast::Sym{quotation};
  case Token::LIST:
    throw "no support for quoted lists yet";
  default:
    throw "quoting something unexpected";
  }
}

Node* Parser::ParseAttrAccess(TokenStream& toks) {
  dt::StrView obj_name = toks.NextToken();
  dt::StrView attr_name = toks.NextToken();

  auto var = module.Symbol(obj_name);
  auto attr = module.Struct(var.Tag())->Attr(attr_name);

  return new AttrAccess{obj_name, attr};
}

std::vector<sym::Param> Parser::CollectParams(TokenStream& toks) {
  std::vector<sym::Param> params;

  while (!toks.NextToken().IsEof()) {
    dt::StrView tok = toks.CurrentToken();

    if (is_type_name(tok)) {
      auto type = TypeByName(tok);
      int count = param_seq_len(toks);

      if (count) {
        for (int i = 0; i < count; ++i) {
          dt::StrView param_name = toks.NextToken();
          params.push_back(Param{param_name, type});
        }
      } else {
        throw "at least 1 typed param";
      }
    } else {
      throw "first id must be a type name";
    }
  }

  return params;
}

std::vector<ast::Node*> Parser::CollectParsed(TokenStream& toks) {
  std::vector<Node*> nodes;

  while (!toks.NextToken().IsEof()) {
    nodes.push_back(ParseToken(toks.CurrentToken()));
  }

  return nodes;
}

Parser::VarInfo Parser::FetchVarInfo(TokenStream& toks) {
  auto name = toks.NextToken();
  auto expr = ParseToken(toks.NextToken());
  auto expr_ty = TypeDeducer::Run(expr);

  if (name.IsList()) {
    lex::TokenStream typed_pair{name};
    auto target_ty = TypeByName(typed_pair.NextToken());
    name = typed_pair.NextToken();

    if (target_ty.SameAs(expr_ty)) {
      return std::make_tuple(name, expr, target_ty);
    } else if (target_ty.CompatibleWith(expr_ty)) {
      auto coerced_expr =
          new IntrinsicCall1{intrinsic::cast(expr_ty, target_ty), expr};

      return std::make_tuple(name, coerced_expr, target_ty);
    } else {
      throw "FetchVarInfo: incompatible type on assignment";
    }
  } else {
    return std::make_tuple(name, expr, expr_ty);
  }
}

ast::Node* Parser::ParseIntrinsicCall1(TokenStream& toks, Type(*lookup)(Type)) {
  auto expr = ParseToken(toks.NextToken());
  auto ty = TypeDeducer::Run(expr);

  return new IntrinsicCall1{lookup(ty), expr};
}
