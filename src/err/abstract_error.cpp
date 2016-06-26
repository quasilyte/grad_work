#include <err/abstract_error.hpp>

using namespace err;

AbstractError::TypeMapper AbstractError::name_by_type = nullptr;

void AbstractError::SetTypeMapper(TypeMapper type_mapper) {
  name_by_type = type_mapper;
}
