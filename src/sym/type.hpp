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
  static Type VOID;
  static Type ANY;
  static Type INT;
  static Type REAL;
  static Type NUM;
  static Type STR;

  Type();
  Type(int id, const char* name, i32 flags);

  int Id() const noexcept;
  i32 Flags() const noexcept;
  const char* Name() const noexcept;

  bool IsVoid() const noexcept;
  bool IsAny() const noexcept;
  bool IsInt() const noexcept;
  bool IsReal() const noexcept;
  bool IsNum() const noexcept;
  bool IsStr() const noexcept;

  bool Arith() const noexcept;
  bool Defined() const noexcept;

  void MarkDefined() noexcept;

  const Type& Merge(const Type&) const noexcept;
  bool CompatibleWith(const Type&) const noexcept;

private:
  const char* name;
  i32 id;
  i32 flags;
};

static_assert(
  sizeof(sym::Type) == 16 || sizeof(sym::Type) == 12,
  "type size expectations failed"
);
