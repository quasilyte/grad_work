#include <frontend/go_cc/fn_parsing.hpp>

#include <lex/char_type.hpp>
#include <unit/globals.hpp>
#include <unit/scope.hpp>
#include <unit/fns.hpp>
#include <unit/source.hpp>
#include <frontend/go_cc/pods/decls.hpp>
#include <frontend/go_cc/common/reader.hpp>
#include <frontend/go_cc/common/types.hpp>
#include <frontend/go_cc/common/reader.hpp>
#include <frontend/go_cc/parsing.hpp>
#include <sym/typedefs.hpp>
#include <err/type_errors.hpp>
#include <macro/blame.hpp>
#include <mn_hash.hpp>

using namespace go_cc;
using namespace chars;

sym::Param collect_param(Reader* reader) {
  auto name = reader->Read(C_IDENT);
  auto type = type_by_name(reader->Skip()->Read(C_IDENT));

  return sym::Param{name, type};
}

sym::ParamList collect_params(Reader reader) {
  sym::ParamList params;

  if (reader.Skip()->CanRead()) {
    for (;;) {
      auto param = collect_param(&reader);
      params.push_back(param);

      if (reader.Skip()->CanRead()) {
        reader.MustConsume(',');
      } else {
        return params;
      }
    }
  } else {
    return params;
  }
}

ast::NodeList collect_exprs(Reader* reader) {
  ast::NodeList exprs;

  while (reader->Skip()->CanRead()) {
    exprs.push_back(parse(reader));
  }

  return exprs;
}

void go_cc::declare_fn(const FnDecl& fn) {
  auto params = collect_params(Reader{fn.params});

  unit::declare_mono_fn(
    fn.name, std::move(params), fn.ret_type
  );
}

void define_fn(Reader* reader, const FnDecl& fn) {
  auto mono_fn = unit::get_mono_fn(fn.name);

  for (const sym::Param& param : mono_fn->Params()) {
    unit::scope_push(param.name, param.type);
  }

  mono_fn->Define(std::move(collect_exprs(reader)));
}

void go_cc::define_fn(const FnDecl& fn) {
  Reader reader{fn.body};

  try {
    unit::create_scope_level();
    ::define_fn(&reader, fn);
    unit::drop_scope_level();
  }
  catch (const err::AbstractError& e) { e.Blame(reader.Pos()); }

  /* catch (err::FnCallArity e) {
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
    BLAME_INDEXED(
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
  }*/
}
