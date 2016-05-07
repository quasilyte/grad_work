#pragma once

#include "typedefs.hpp"

namespace sym {
  class Type;
}

class sym::Type {
public:
  enum Category: i32 {
    ANY, // Compatible with all categories
    EITHER, // Exactly one of the two compatible types
    NUM, // Integers, floats
    CLASS, // User defined types (optionally can have hierarchical relations)
    STRICT, // Single type
    BEGIN_CALLABLE,
    USER_FUNC,
    BUILTIN_FUNC,
    MACRO,
    END_CALLABLE,
    VOID,
  };

  constexpr Type(int id, const char* name, Category category):
  name{name}, id{id}, category{category} {}

  int Id() const noexcept;
  Category Category() const noexcept;
  const char* Name() const noexcept;

  bool IsAny() const noexcept;
  bool IsEither() const noexcept;
  bool IsNumeric() const noexcept;
  bool IsClass() const noexcept;
  bool IsUserFunc() const noexcept;
  bool IsBuiltinFunc() const noexcept;
  bool IsMacro() const noexcept;
  bool IsCallable() const noexcept;

  // Type LeastUpperBound

  bool CompatibleWith(Type) const noexcept;

private:
  const char* name;
  int id;
  enum Category category;
};

static_assert(
  sizeof(sym::Type) == 16 || sizeof(sym::Type) == 12,
  "type size expectations failed"
);
