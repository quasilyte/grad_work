#pragma once

#include "dt/str_view.hpp"
#include "sym/type.hpp"
#include "sym/param.hpp"

namespace sym {
  struct Fn;
}

namespace err {
  struct FnCallArity;
  struct FnCallArgType;
  struct UndefinedSymbol;
  struct UnexpectedKeyword;
  struct UnexpectedToken;
  struct MixedArithTypes;
  struct SkipUntilFailure;
  struct NonBoolCondition;
  struct InvalidTypeInArith;
}

struct err::MixedArithTypes {
  sym::Type lhs_type;
  sym::Type rhs_type;
  const char* op_symbol;
};

struct err::FnCallArity {
  dt::StrView fn_name;
  sym::Fn* fn;
  uint args_given;
};

struct err::FnCallArgType {
  dt::StrView fn_name;
  sym::Param arg;
  sym::Type type_given;
};

struct err::UndefinedSymbol {
  dt::StrView name;
};

struct err::UnexpectedKeyword {
  const char* given_keyword;
  const char* expected_what;
};

struct err::SkipUntilFailure {
  char target;
};

struct err::NonBoolCondition {
  sym::Type cond_type;
};

struct err::InvalidTypeInArith {
  sym::Type given_type;
  const char* op_symbol;
};

struct err::UnexpectedToken {
  char token[4];
};
