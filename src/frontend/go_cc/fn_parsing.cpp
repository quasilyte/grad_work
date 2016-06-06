#include <frontend/go_cc/fn_parsing.hpp>

#include <lex/char_type.hpp>
#include <unit/globals.hpp>
#include <unit/scope.hpp>
#include <unit/fns.hpp>
#include <unit/source.hpp>
#include <frontend/go_cc/reader.hpp>
#include <frontend/go_cc/char_groups.hpp>
#include <frontend/go_cc/decl.hpp>
#include <frontend/go_cc/types.hpp>
#include <frontend/go_cc/cursor_ext.hpp>
#include <frontend/go_cc/parsing.hpp>
#include <sym/typedefs.hpp>
#include <lex/cursor.hpp>
#include <errors.hpp>
#include <mn_hash.hpp>

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

ast::NodeList collect_exprs(Cursor* cur) {
  ast::NodeList exprs;

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
    BLAME(
      "function {%.*s} expects {%u} arguments, {%u} given",
      &cur,
      BUF_FMT(e.fn_name),
      e.fn->Arity(),
      e.args_given
    );
  } catch (err::FnCallArgType e) {
    BLAME(
      "function {%.*s} {%.*s} param has type {%s}, {%s} given",
      &cur,
      BUF_FMT(e.fn_name),
      BUF_FMT(e.arg.name),
      name_by_type(e.arg.type),
      name_by_type(e.type_given)
    );
  } catch (err::UndefinedSymbol e) {
    BLAME("symbol {%.*s} is undefined", &cur, BUF_FMT(e.name));
  } catch (err::UnexpectedKeyword e) {
    BLAME(
      "unexpected {%s}, expecting {%s}", &cur, e.given_keyword, e.expected_what
    );
  } catch (err::MixedArithTypes e) {
    BLAME_POSITIONAL(
      "expected {%2$s %3$s %2$s}, found {%2$s %3$s %4$s}",
      &cur,
      name_by_type(e.lhs_type),
      e.op_symbol,
      name_by_type(e.rhs_type)
    );
  } catch (err::NonBoolCondition e) {
    BLAME(
      "only bool is alowed inside conditional, got {%s}",
      &cur,
      name_by_type(e.cond_type)
    );
  } catch (err::InvalidTypeInArith e) {
    BLAME(
      "{%s} expects int|real type, {%s} given",
      &cur,
      e.op_symbol,
      name_by_type(e.given_type)
    );
  } catch (err::UnexpectedToken e) {
    BLAME("operator {%s} does not exist", &cur, e.token);
  }
}
