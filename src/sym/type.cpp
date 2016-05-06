#include "sym/type.hpp"

using namespace sym;

int Type::get_id() const noexcept {
  return id;
}

Type::Category Type::get_category() const noexcept {
  return category;
}

const char* Type::get_name() const noexcept {
  return name;
}

bool Type::is_any() const noexcept {
  return category == ANY;
}

bool Type::is_either() const noexcept {
  return category == EITHER;
}

bool Type::is_numeric() const noexcept {
  return category == NUM;
}

bool Type::is_class() const noexcept {
  return category == CLASS;
}

bool Type::is_user_func() const noexcept {
  return category == USER_FUNC;
}

bool Type::is_builtin_func() const noexcept {
  return category == BUILTIN_FUNC;
}

bool Type::is_macro() const noexcept {
  return category == MACRO;
}

bool Type::is_callable() const noexcept {
  return category > BEGIN_CALLABLE && category < END_CALLABLE;
}

bool Type::compatible_with(Type other) const noexcept {
  if (id == other.id) {
    return true;
  }

  // Could be rewritten to bool[][] table
  switch (category) {
  case ANY: return true;
  case EITHER: throw "eithers compat not implemented";
  case NUM: return other.is_numeric();
  case CLASS: throw "classes compat not implemented";
  case USER_FUNC: throw "user_func compat not implemented";
  case BUILTIN_FUNC: throw "user_func compat not implemented";
  case MACRO: throw "macro compat not implemented";

  default:
    throw "invalid category!";
  }
}
