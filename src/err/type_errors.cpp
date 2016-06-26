#include <err/type_errors.hpp>

#include <macro/blame.hpp>

using namespace err;
using sym::Type;
using dt::StrView;

MixedArithTypes::MixedArithTypes(Type lhs, Type rhs, const char* op_symbol):
lhs_type{lhs}, rhs_type{rhs}, op_symbol{op_symbol} {}

void MixedArithTypes::Blame(const char* error_location) const {
  BLAME_INDEXED(
    "expected {%2$s %3$s %2$s}, found {%2$s %3$s %4$s}",
    error_location,
    name_by_type(lhs_type),
    op_symbol,
    name_by_type(rhs_type)
  );
}

InvalidTypeInArith::InvalidTypeInArith(Type given, const char* op_symbol):
given_type{given}, op_symbol{op_symbol} {}

void InvalidTypeInArith::Blame(const char* error_location) const {
  BLAME(
    "{%s} expects int|real type, {%s} given",
    error_location,
    op_symbol,
    name_by_type(given_type)
  );
}

VarTypeMismatch::VarTypeMismatch(Type expected, Type given, StrView name):
expected_type{expected}, given_type{given}, var_name{name} {}

void VarTypeMismatch::Blame(const char* error_location) const {
  BLAME(
    "{%.*s} expects expr of type {%s}, {%s} given",
    error_location,
    BUF_FMT(var_name),
    name_by_type(expected_type),
    name_by_type(given_type)
  );
}
