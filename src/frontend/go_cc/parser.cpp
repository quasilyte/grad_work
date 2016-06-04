#include "frontend/go_cc/parser.hpp"

#include "unit/globals.hpp"
#include "unit/scope.hpp"
#include "unit/fns.hpp"
#include "frontend/go_cc/expr_parsing.hpp"
#include "frontend/go_cc/fn_parsing.hpp"

using namespace go_cc;
using namespace lex;

void Parser::Run(const TopLevel& top) {
  Parser self{top};
  self.Parse();
}

Parser::Parser(const TopLevel& top): top{top} {}

void Parser::Parse() {
  for (go_cc::TypedDecl global : top.typed_globals) {
    unit::def_global(
      global.name,
      parse_expr(global.init, "\n;"),
      global.type
    );
  }

  for (go_cc::Decl global : top.globals) {
    auto expr = parse_expr(global.init, "\n;");
    unit::def_global(
      global.name,
      expr,
      expr->Type()
    );
  }

  for (const go_cc::FnDecl& fn : top.fns) {
    parse_fn(fn);
  }
}
