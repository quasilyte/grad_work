#include <sym/qualified_id.hpp>

using namespace sym;

QualifiedId::QualifiedId(dt::StrView pkg_name, dt::StrView identifier):
pkg_name{pkg_name}, identifier{identifier} {}

bool QualifiedId::operator==(const QualifiedId& other) const {
  return other.pkg_name == pkg_name
      && other.identifier == identifier;
}
