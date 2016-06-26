#include <frontend/go_cc/stmt_parsing.hpp>

#include <ast/builtins.hpp>
#include <ast/defs.hpp>
#include <ast/cond.hpp>
#include <ast/statements.hpp>
#include <frontend/go_cc/expr_parsing.hpp>
#include <frontend/go_cc/parsing.hpp>
#include <frontend/go_cc/common/reader.hpp>
#include <unit/scope.hpp>
#include <cc/strict/arith.hpp>
#include <cc/strict/statements.hpp>

using namespace chars;

ast::Node* go_cc::parse_assignment(dt::StrView name, Reader* reader) {
  auto expr = parse_expr(reader->Skip()->ReadExpr());
  return cc::strict_assign(name, expr);
}

ast::Node* go_cc::parse_return(Reader* reader) {
  auto expr = parse_expr(reader->Skip()->ReadExpr());
  return new ast::Return{expr};
}

ast::Node* go_cc::parse_short_var_decl(dt::StrView id, Reader* reader) {
  auto expr = parse_expr(reader->Skip()->ReadExpr());
  auto type = expr->Type();

  unit::scope_push(id, type);
  return new ast::DefVar{id, expr, type};
}

ast::Node* go_cc::parse_plus_assignment(dt::StrView id, Reader* reader) {
  auto expr = parse_expr(reader->Skip()->ReadExpr());
  return cc::strict_sum_assign(id, expr);
}

ast::Node* go_cc::parse_if(Reader* cur) {
  throw 'f';
  /*
  ast::NodeList on_true;
  ast::NodeList on_false;

  auto cond = parse_expr(skip(cur, SPACES), "{");
  skip(cur, 1);

  unit::create_scope_level();
  while (!try_consume(skip(cur, SPACES), '}')) {
    on_true.push_back(parse(cur));
  }
  unit::drop_scope_level();

  unit::create_scope_level();
  if (try_consume(skip(cur, SPACES), "else")) {

    if (try_consume(skip(cur, SPACES), '{')) {
      while (!try_consume(skip(cur, SPACES), '}')) {
        on_false.push_back(parse(cur));
      }
    } else {
      throw "expected `{`";
    }
  }
  unit::drop_scope_level();

  return cc::strict_if_stmt(cond, std::move(on_true), std::move(on_false));
  */
}
