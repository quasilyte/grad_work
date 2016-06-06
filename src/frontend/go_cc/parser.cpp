#include <frontend/go_cc/parser.hpp>

#include <unit/globals.hpp>
#include <unit/scope.hpp>
#include <unit/fns.hpp>
#include <unit/structs.hpp>
#include <frontend/go_cc/expr_parsing.hpp>
#include <frontend/go_cc/fn_parsing.hpp>
#include <frontend/go_cc/type_parsing.hpp>
#include <lex/cursor.hpp>
#include <errors.hpp>

using namespace go_cc;
using namespace lex;

void Parser::Run(const TopLevel& top) {
  Parser self{top};
  self.Parse();
}

Parser::Parser(const TopLevel& top): top{top} {}

void Parser::Parse() {
  for (const go_cc::StructDecl& st : top.structs) {
    declare_struct(st);
  }

  for (const go_cc::StructDecl& st : top.structs) {
    define_struct(st);
  }

  for (const go_cc::FnDecl& fn : top.fns) {
    declare_fn(fn);
  }

  for (go_cc::TypedDecl global : top.typed_globals) {
    unit::def_global(
      global.name,
      parse_expr(global.init),
      global.type
    );
  }

  for (go_cc::Decl global : top.globals) {
    auto expr = parse_expr(global.init);
    unit::def_global(
      global.name,
      expr,
      expr->Type()
    );
  }

  for (const go_cc::FnDecl& fn : top.fns) {
    define_fn(fn);
  }
}
