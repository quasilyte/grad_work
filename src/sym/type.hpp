#pragma once

#include "typedefs.hpp"

namespace sym {
  class Type;

  namespace flags {
    static const i32 ARITH = 1 << 0;
    static const i32 DEFINED = 1 << 1;
  }
}

class sym::Type {
public:
  // Builtin types defined only once
  static const Type VOID;
  static const Type ANY;
  static const Type INT;
  static const Type REAL;
  static const Type NUM;
  static const Type STR;

  Type(const char* name);

  const char* Name() const noexcept;

  bool IsVoid() const noexcept;
  bool IsAny() const noexcept;
  bool IsInt() const noexcept;
  bool IsReal() const noexcept;
  bool IsNum() const noexcept;
  bool IsStr() const noexcept;
  bool IsFunc() const noexcept; // #FIXME

  bool Arith() const noexcept;

  const Type* Merge(const Type*) const noexcept;
  bool CompatibleWith(const Type*) const noexcept;
  bool SameAs(const Type*) const noexcept;

private:
  const char* name;
};

/*
static_assert(
  sizeof(sym::Type) == 16 || sizeof(sym::Type) == 12,
  "type size expectations failed"
);
*/
