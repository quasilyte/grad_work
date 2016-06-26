#include <cc/strict/type_check.hpp>

#include <err/type_errors.hpp>

using namespace cc;

void cc::strict_type_check(dt::StrView name, sym::Type a, sym::Type b) {
  if (!a.SameAs(b)) {
    throw err::VarTypeMismatch{a, b, name};
  }
}
