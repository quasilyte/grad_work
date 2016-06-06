#include "frontend/go_cc/fn_parsing.hpp"

#include "lex/char_type.hpp"
#include "unit/globals.hpp"
#include "unit/scope.hpp"
#include "unit/fns.hpp"
#include "frontend/go_cc/reader.hpp"
#include "frontend/go_cc/char_groups.hpp"
#include "frontend/go_cc/decl.hpp"
#include "frontend/go_cc/types.hpp"
#include "frontend/go_cc/cursor_ext.hpp"
#include "frontend/go_cc/parsing.hpp"
#include "sym/typedefs.hpp"
#include "lex/cursor.hpp"
#include "errors.hpp"
#include "mn_hash.hpp"

using namespace go_cc;
using namespace lex;


sym::ParamList collect_params(Cursor cur) {
  sym::ParamList params;

  while (can_read(skip(&cur, SPACES))) {
    auto name = next_ident(&cur);
    auto type = type_by_name(next_ident(&cur));

    if (!try_consume(skip(&cur, SPACES), ',') && can_read(&cur)) {
      throw "expected `,`";
    }

    params.push_back(sym::Param{name, type});
  }

  return params;
}

std::vector<ast::Node*> collect_exprs(Cursor* cur) {
  std::vector<ast::Node*> exprs;

  while (can_read(skip(cur, SPACES))) {
    exprs.push_back(parse(cur));
  }

  return exprs;
}

void parse_fn_decl(const FnDecl& fn, Cursor* cur) {
  auto params = collect_params(Cursor{fn.params});

  for (const sym::Param& param : params) {
    unit::scope_push(param.name, param.type);
  }

  auto mono_fn = unit::declare_mono_fn(
    fn.name, std::move(params), fn.ret_type
  );

  mono_fn->Define(std::move(collect_exprs(cur)));
}

void go_cc::declare_fn(const FnDecl& fn) {
  auto params = collect_params(Cursor{fn.params});

  unit::declare_mono_fn(
    fn.name, std::move(params), fn.ret_type
  );
}

void define_fn(Cursor* cur, const FnDecl& fn) {
  auto mono_fn = unit::get_mono_fn(fn.name);

  for (const sym::Param& param : mono_fn->Params()) {
    unit::scope_push(param.name, param.type);
  }

  mono_fn->Define(std::move(collect_exprs(cur)));
}

void go_cc::define_fn(const FnDecl& fn) {
  Cursor cur{fn.body};

  try {
    unit::create_scope_level();
    ::define_fn(&cur, fn);
    unit::drop_scope_level();
  } catch (err::FnCallArity e) {
    std::fprintf(
      stderr,
      "line %d: "
      "function {%.*s} expects {%u} arguments, {%u} given\n",
      line_number(&cur),
      e.fn_name.Len(),
      e.fn_name.Data(),
      e.fn->Arity(),
      e.args_given
    );
  } catch (err::FnCallArgType e) {
    auto type_expected_name = name_by_type(e.arg.type);
    auto type_given_name = name_by_type(e.type_given);

    std::fprintf(
      stderr,
      "line %d: "
      "function {%.*s} {%.*s} param has type {%s}, {%s} given\n",
      line_number(&cur),
      e.fn_name.Len(),
      e.fn_name.Data(),
      e.arg.name.Len(),
      e.arg.name.Data(),
      type_expected_name,
      type_given_name
    );
  } catch (err::UndefinedSymbol e) {
    std::fprintf(
      stderr,
      "line %d: "
      "symbol {%.*s} is undefined\n",
      line_number(&cur),
      e.name.Len(),
      e.name.Data()
    );
  } catch (err::UnexpectedKeyword e) {
    std::fprintf(
      stderr,
      "line %d: "
      "unexpected {%s}, expecting {%s}\n",
      line_number(&cur),
      e.given_keyword,
      e.expected_what
    );
  } catch (err::MixedArithTypes e) {
    auto lhs_type_name = name_by_type(e.lhs_type);
    auto rhs_type_name = name_by_type(e.rhs_type);

    std::fprintf(
      stderr,
      "line %d: "
      "expected {%s %s %s}, found {%s %s %s}\n",
      line_number(&cur),
      lhs_type_name,
      e.op_symbol,
      lhs_type_name,
      lhs_type_name,
      e.op_symbol,
      rhs_type_name
    );
  } catch (err::NonBoolCondition e) {
    auto cond_type_name = name_by_type(e.cond_type);

    std::fprintf(
      stderr,
      "line %d: "
      "only bool is alowed inside conditional, got {%s}\n",
      line_number(&cur),
      cond_type_name
    );
  } catch (err::InvalidTypeInArith e) {
    auto given_type_name = name_by_type(e.given_type);

    std::fprintf(
      stderr,
      "line %d: "
      "{%s} expects int|real type, {%s} given\n",
      line_number(&cur),
      e.op_symbol,
      given_type_name
    );
  } catch (err::UnexpectedToken e) {
    std::fprintf(
      stderr,
      "line %d: "
      "operator {%s} does not exist\n",
      line_number(&cur),
      e.token
    );
  }
}
