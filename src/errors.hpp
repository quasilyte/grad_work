#pragma once

#include <dt/str_view.hpp>
#include <sym/type.hpp>
#include <sym/param.hpp>

namespace sym {
  struct Fn;
}

#define BLAME(FORMAT, LINE_NUMBER_PROVIDER, ...) \
  std::fprintf( \
    stderr, \
    "line %d: " \
    FORMAT \
    "\n", \
    unit::get_line_number(LINE_NUMBER_PROVIDER), \
    __VA_ARGS__ \
  )

#define BLAME_POSITIONAL(FORMAT, LINE_NUMBER_PROVIDER, ...) \
  std::fprintf( \
    stderr, \
    "line %1$d: " \
    FORMAT \
    "\n", \
    unit::get_line_number(LINE_NUMBER_PROVIDER), \
    __VA_ARGS__ \
  )

#define BUF_FMT(X) \
  X.Len(), \
  X.Data()

namespace err {
  struct FnCallArity;
  struct FnCallArgType;
  struct UndefinedSymbol;
  struct UndefinedType;
  struct UnexpectedKeyword;
  struct UnexpectedToken;
  struct MixedArithTypes;
  struct SkipUntilFailure;
  struct NonBoolCondition;
  struct InvalidTypeInArith;
  struct Redefinition;
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

struct err::UndefinedType {
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

struct err::Redefinition {
  dt::StrView name;
  const char* type;
};
