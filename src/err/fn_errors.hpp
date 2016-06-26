#pragma once

#include <err/abstract_error.hpp>
#include <dt/str_view.hpp>
#include <sym/fn.hpp>

namespace err {
  struct FnCallArity;
  struct FnCallArgType;
}

struct err::FnCallArity: AbstractError {
  FnCallArity(dt::StrView fn_name, sym::Fn*, uint args_given);

  void Blame(const char* error_location) const override;

  dt::StrView fn_name;
  sym::Fn* fn;
  uint args_given;
};

struct err::FnCallArgType: AbstractError {
  FnCallArgType(dt::StrView fn_name, sym::Param arg, sym::Type type_given);

  void Blame(const char* error_location) const override;

  dt::StrView fn_name;
  sym::Param arg;
  sym::Type type_given;
};
