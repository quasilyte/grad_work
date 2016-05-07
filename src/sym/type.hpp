#pragma once

namespace sym {
  class Type;
}

class sym::Type {
public:
  enum Category: int {
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

  int get_id() const noexcept;
  Category get_category() const noexcept;
  const char* get_name() const noexcept;

  bool is_any() const noexcept;
  bool is_either() const noexcept;
  bool is_numeric() const noexcept;
  bool is_class() const noexcept;
  bool is_user_func() const noexcept;
  bool is_builtin_func() const noexcept;
  bool is_macro() const noexcept;
  bool is_callable() const noexcept;

  // Type LeastUpperBound

  bool compatible_with(Type) const noexcept;

private:
  const char* name;
  int id;
  Category category;
};

static_assert(
  sizeof(sym::Type) == 16 || sizeof(sym::Type) == 12,
  "type size expectations failed"
);
