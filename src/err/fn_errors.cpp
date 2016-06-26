#include <err/fn_errors.hpp>

#include <macro/blame.hpp>

using namespace err;
using dt::StrView;
using sym::Param;
using sym::Type;
using sym::Fn;

FnCallArity::FnCallArity(StrView fn_name, sym::Fn* fn, uint args_given):
fn_name{fn_name}, fn{fn}, args_given{args_given} {}

void FnCallArity::Blame(const char* error_location) const {
  BLAME(
    "function {%.*s} expects {%u} arguments, {%u} given",
    error_location,
    BUF_FMT(fn_name),
    fn->Arity(),
    args_given
  );
}

FnCallArgType::FnCallArgType(StrView fn_name, Param arg, Type type_given) {}
// fn_name{fn_name}, arg{arg}, type_given{type_given} {}

void FnCallArgType::Blame(const char* error_location) const {
  BLAME(
    "function {%.*s} {%.*s} param has type {%s}, {%s} given",
    error_location,
    BUF_FMT(fn_name),
    BUF_FMT(arg.name),
    name_by_type(arg.type),
    name_by_type(type_given)
  );
}
