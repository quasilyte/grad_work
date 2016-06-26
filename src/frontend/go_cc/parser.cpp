#include <frontend/go_cc/parser.hpp>

#include <unit/globals.hpp>
#include <unit/scope.hpp>
#include <unit/fns.hpp>
#include <unit/structs.hpp>
#include <unit/source.hpp>
#include <frontend/go_cc/expr_parsing.hpp>
#include <frontend/go_cc/fn_parsing.hpp>
#include <frontend/go_cc/type_parsing.hpp>
#include <frontend/go_cc/common/types.hpp>
#include <cc/strict/type_check.hpp>

#include <err/type_errors.hpp>
#include <macro/blame.hpp>

using namespace go_cc;
using namespace lex;

void Parser::Run(const TopLevel& top) {
  Parser self{top};
  self.Parse();
}

Parser::Parser(const TopLevel& top): top{top} {}

void Parser::Parse() {
  err::AbstractError::SetTypeMapper(name_by_type);

  /*
  for (const go_cc::StructDecl& st : top.structs) {
    declare_struct(st);
  }

  for (const go_cc::StructDecl& st : top.structs) {
    define_struct(st);
  }


  */
  for (const go_cc::FnDecl& fn : top.fns) {
    declare_fn(fn);
  }

  for (const go_cc::VarDecl& global : top.globals) {
    try {
      auto expr = parse_expr(global.init);
      if (global.type.IsUnknown()) {
        unit::def_global(global.name, expr, expr->Type());
      } else {
        cc::strict_type_check(global.name, global.type, expr->Type());
        unit::def_global(global.name, expr, global.type);
      }
    }
    catch (const err::AbstractError& e) { e.Blame(global.name.Data()); }
  }

  if (0 == unit::get_error_count()) {
    for (const go_cc::FnDecl& fn : top.fns) {
      define_fn(fn);
    }
  }
}
