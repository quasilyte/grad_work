#include "sym/type.hpp"

using namespace sym;

int Type::Id() const noexcept {
  return id;
}

enum Type::Category Type::Category() const noexcept {
  return category;
}

const char* Type::Name() const noexcept {
  return name;
}

bool Type::IsAny() const noexcept {
  return category == ANY;
}

bool Type::IsEither() const noexcept {
  return category == EITHER;
}

bool Type::IsNumeric() const noexcept {
  return category == NUM;
}

bool Type::IsClass() const noexcept {
  return category == CLASS;
}

bool Type::IsUserFunc() const noexcept {
  return category == USER_FUNC;
}

bool Type::IsBuiltinFunc() const noexcept {
  return category == BUILTIN_FUNC;
}

bool Type::IsMacro() const noexcept {
  return category == MACRO;
}

bool Type::IsCallable() const noexcept {
  return category > BEGIN_CALLABLE && category < END_CALLABLE;
}

bool Type::CompatibleWith(Type other) const noexcept {
  if (id == other.id) {
    return true;
  }

  // Could be rewritten to bool[][] table
  switch (category) {
  case ANY: return true;
  case EITHER: throw "eithers compat not implemented";
  case NUM: return other.IsNumeric();
  case CLASS: throw "classes compat not implemented";
  case USER_FUNC: throw "user_func compat not implemented";
  case BUILTIN_FUNC: throw "user_func compat not implemented";
  case MACRO: throw "macro compat not implemented";

  default:
    throw "invalid category!";
  }
}
