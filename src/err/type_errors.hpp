#pragma once

#include <dt/str_view.hpp>
#include <sym/type.hpp>
#include <err/abstract_error.hpp>

namespace err {
  struct MixedArithTypes;
  struct InvalidTypeInArith;
  struct UndefinedType;
  struct NonBoolCondition;
  struct VarTypeMismatch;
}

struct err::UndefinedType {
  dt::StrView name;
};

struct err::MixedArithTypes: AbstractError {
  MixedArithTypes(sym::Type lhs, sym::Type rhs, const char* op_symbol);

  void Blame(const char* error_location) const override;

  sym::Type lhs_type;
  sym::Type rhs_type;
  const char* op_symbol;
};

struct err::InvalidTypeInArith: AbstractError {
  InvalidTypeInArith(sym::Type given, const char* op_symbol);

  void Blame(const char* error_location) const override;

  sym::Type given_type;
  const char* op_symbol;
};

struct err::NonBoolCondition {
  sym::Type cond_type;
};

struct err::VarTypeMismatch: AbstractError {
  VarTypeMismatch(sym::Type expected, sym::Type given, dt::StrView name);

  void Blame(const char* error_location) const override;

  sym::Type expected_type;
  sym::Type given_type;
  dt::StrView var_name;
};
