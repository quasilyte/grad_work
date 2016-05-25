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
#include "unit/fns.hpp"
#include "util/std_vector.hpp"
#include "unit/syms.hpp"
#include "unit/structs.hpp"
#include "sym/rules.hpp"
#include <algorithm>

#include "dbg/lex.hpp"

using namespace cc;
using namespace lex;
using namespace ast;
using namespace dt;
using namespace sym;

void expect(bool expr, const char* msg) {
  if (!expr) {
    throw msg;
  }
}

int param_seq_len(lex::TokenStream toks) {
  int result = 0;

  while (!toks.NextToken().IsEof()
         && !is_type_name(toks.CurrentToken())) {
    result += 1;
  }

  return result;
}

Node* resolve_named_call(std::vector<Node*>&& args, MultiFn* multi_fn) {
  // #FIXME: should warn if there is no static variant found
  // and arguments type are not "all Any".

  auto types = util::map(args, TypeDeducer::Run);

  auto named_fn = multi_fn->Find(types);

  if (named_fn) {
    auto is_fallback =
        std::all_of(types.begin(), types.end(), [](Type t){ return t.IsAny(); });

    if (is_fallback) {
      return new DynamicCall{multi_fn, std::move(args)};
    } else {
      return new FuncCall{named_fn, std::move(args)};
    }
  } else {
    return new DynamicCall{multi_fn, std::move(args)};
  }
}

int length(TokenStream toks) {
  int size = 0;

  while (!toks.NextToken().IsEof()) {
    size += 1;
  }

  return size;
}

sym::Type Parser::TypeByName(dt::StrView name) const {
  using namespace mn_hash;

  switch (encode9(name.Data(), name.Len())) {
  case encode9("Int"): return Type::Int();
  case encode9("Real"): return Type::Real();
  case encode9("Any"): return Type::Any();
  case encode9("Str"): return Type::Str();

  default:
    auto st = unit::get_struct(name);
    expect(st, "TypeByName: unknown type");
    return st->type;
  }
}

TranslationUnit Parser::Run(const TopLevel& top) {
  Parser self{top};
  auto tu = self.Parse();

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
  std::vector<sym::Param> attrs = CollectParams(toks);

  if (attrs.size()) {
    unit::def_struct(name, std::move(attrs));
  } else {
    throw "struct must have at least 1 named field";
  }
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
  unit::def_global(name, ty);
}

void Parser::ParseExpr(Token& tok) {
  if (tok.IsList()) {
    result.exprs.push_back(ParseList(tok));
  } else {
    result.exprs.push_back(ParseToken(tok));
  }
}

Node* Parser::ParseLambdaExpr(TokenStream& toks) {
  TokenStream signature{toks.NextToken()};
  auto params = CollectParams(signature);

  module.CreateScopeLevel();
  for (const sym::Param& param : params) {
    module.DefineLocal(param.name, param.type);
  }
  auto exprs = CollectParsed(toks);
  auto ret_ty = TypeDeducer::Run(exprs.back());
  module.DropScopeLevel();

  return new LambdaExpr{
    unit::new_unnamed_fn(std::move(params), std::move(exprs), ret_ty)
  };
}

void Parser::ParseSignature(TokenStream& toks) {
  lex::TokenStream signature{toks.NextToken()};
  MultiFn::Key sig_matcher;

  auto name = signature.NextToken();
  auto params = CollectParams(signature);

  module.CreateScopeLevel();

  for (const sym::Param& param : params) {
    sig_matcher.push_back(param.type);
    module.DefineLocal(param.name, param.type);
  }

  auto named_fn = unit::declare_named_fn(name, std::move(params), sig_matcher);

  auto exprs = CollectParsed(toks);
  auto ty = TypeDeducer::Run(exprs.back());
  module.DropScopeLevel();

  named_fn->Define(std::move(exprs), ty);
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
    case encode9("each"): return ParseEach(list);
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
  case encode9("real"): return new Intrinsic{Type::ANY_TO_REAL};
  case encode9("int"): return new Intrinsic{Type::ANY_TO_INT};

  default:
    return new Var{word, module.SymbolOrFunc(word)};
  }
}

ast::Node* Parser::ParseFuncCall(lex::Token& name, lex::TokenStream& toks) {
  auto args = CollectParsed(toks);
  sym::MultiFn* multi_fn = unit::get_multi_fn(name);

  if (multi_fn) {
    return resolve_named_call(std::move(args), multi_fn);
  } else {
    auto callable = module.Symbol(name);

    if (callable.IsAny()) {
      // How to call Any:
      // 1) at run time check if tag belongs to funcs, panic if not
      // 2) fetch function by tag, check arity
      // 3) call dynamic dispatcher for args
      throw "FuncCall: polymorphic call is not supported yet";
    } else if (callable.IsFunc()) {
      auto func = unit::get_fn(callable);
      expect(func->Arity() == args.size(), "arity mismatch");
      for (uint i = 0; i < func->Arity(); ++i) {
        if (!func->Params()[i].type.SameAs(TypeDeducer::Run(args[i]))) {
          throw "type mismatch";
        }
      }
      return new VarCall{name, func, std::move(args)};
    } else if (callable.IsDynDispatcher()) {
      MultiFn* multi_fn = unit::get_multi_fn(callable.Tag());
      expect(multi_fn->arity == args.size(), "arity mismatch");

      return resolve_named_call(std::move(args), multi_fn);
    } else {
      throw "FuncCall: called something that can not be called";
    }
  }
}

Node* Parser::ParseEach(TokenStream& toks) {
  auto iter_name = toks.NextToken();
  auto seq_expr = ParseToken(toks.NextToken());
  auto seq_type = TypeDeducer::Run(seq_expr);

  sym::NamedFn* next_fn = unit::get_multi_fn("next")->Find({seq_type});
  sym::NamedFn* has_next_fn = unit::get_multi_fn("has_next")->Find({seq_type});
  sym::NamedFn* current_fn = unit::get_multi_fn("current")->Find({seq_type});
  expect(next_fn, "next for type not found");
  expect(has_next_fn, "has_next_fn for type not found");
  expect(current_fn, "current for type not found");

  module.CreateScopeLevel();
  module.DefineLocal(iter_name, current_fn->ret_type);
  auto body_expr = ParseToken(toks.NextToken());
  module.DropScopeLevel();

  return new Each{
    seq_expr,
    body_expr,
    next_fn,
    has_next_fn,
    current_fn,
    iter_name
  };
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
    auto attr = unit::get_struct(var)->Attr(attr_name);

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
  auto st = unit::get_struct(toks.NextToken());

  if (st) {
    std::vector<Node*> initializers;
    while (!toks.NextToken().IsEof()) {
      initializers.push_back(ParseToken(toks.CurrentToken()));
    }

    return new CompoundLiteral{std::move(initializers), st->type};
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
    auto attr = unit::get_struct(var)->Attr(static_cast<Sym*>(key)->datum);
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
  auto attr = unit::get_struct(var)->Attr(attr_name);

  return new AttrAccess{obj_name, attr};
}

std::vector<sym::Param> Parser::CollectParams(TokenStream& toks) {
  std::vector<sym::Param> params;

  while (!toks.NextToken().IsEof()) {
    dt::StrView tok = toks.CurrentToken();
    expect(is_type_name(tok), "first id must be a type name");

    auto type = TypeByName(tok);
    int count = param_seq_len(toks);
    expect(count, "at least 1 typed param");

    for (int i = 0; i < count; ++i) {
      dt::StrView param_name = toks.NextToken();
      params.push_back(Param{param_name, type});
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
  switch (length(toks)) {
  case 2: { // Infer type from assignment
    auto name = toks.NextToken();
    auto expr = ParseToken(toks.NextToken());
    auto expr_type = TypeDeducer::Run(expr);

    return std::make_tuple(name, expr, expr_type);
  }
  case 3: { // With explicit type info
    auto type_name = toks.NextToken();
    auto name = toks.NextToken();
    auto expr = ParseToken(toks.NextToken());
    auto expr_type = TypeDeducer::Run(expr);

    expect(sym::is_type_name(type_name), "var: not a type name");

    auto type = TypeByName(type_name);

    if (type.SameAs(expr_type)) {
      return std::make_tuple(name, expr, type);
    } else {
      auto coerced_expr =
          new IntrinsicCall1{intrinsic::cast(expr_type, type), expr};

      return std::make_tuple(name, coerced_expr, type);
    }
  }
  default:
    throw "var: arity mismatch";
  }
}

ast::Node* Parser::ParseIntrinsicCall1(TokenStream& toks, Type(*lookup)(Type)) {
  auto expr = ParseToken(toks.NextToken());
  auto ty = TypeDeducer::Run(expr);

  return new IntrinsicCall1{lookup(ty), expr};
}
