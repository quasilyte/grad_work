#pragma once

#include "typedefs.hpp"
#include <limits>

namespace sym {
  class Type;
}

class sym::Type {
public:
  typedef i32 Id;

  static const Id VOID = std::numeric_limits<Id>::max();
  static const Id END_ARITH = std::numeric_limits<Id>::max() - 1;
  static const Id ANY = std::numeric_limits<Id>::max() - 2;
  static const Id NUM = std::numeric_limits<Id>::max() - 3;
  static const Id REAL = std::numeric_limits<Id>::max() - 4;
  static const Id INT = std::numeric_limits<Id>::max() - 5;
  static const Id UNKNOWN = std::numeric_limits<Id>::max() - 6;
  static const Id BEGIN_ARITH = std::numeric_limits<Id>::max() - 7;
  static const Id STR = std::numeric_limits<Id>::max() - 8;
  static const Id SYM = std::numeric_limits<Id>::max() - 9;
  static const Id END_STRUCT = std::numeric_limits<Id>::max() - 10;

  static Type Void();
  static Type Any();
  static Type Num();
  static Type Real();
  static Type Int();
  static Type Unknown();
  static Type Str();
  static Type Sym();

  Type();
  Type(const Type&);
  Type(Id Tag);

  Id Tag() const noexcept;

  bool IsVoid() const noexcept;
  bool IsAny() const noexcept;
  bool IsInt() const noexcept;
  bool IsUnknown() const noexcept;
  bool IsReal() const noexcept;
  bool IsNum() const noexcept;
  bool IsStr() const noexcept;
  bool IsSym() const noexcept;

  bool IsArith() const noexcept;
  bool IsStruct() const noexcept;

  Type ExtendedWith(Type);
  void ExtendWith(Type);

  bool CompatibleWith(Type) const noexcept;
  bool SameAs(Type) const noexcept;

private:
  Id tag;
};

/*
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

  bool Arith() const noexcept;

  const Type* Merge(const Type*) const noexcept;
  bool CompatibleWith(const Type*) const noexcept;
  bool SameAs(const Type*) const noexcept;

private:
  const char* name;
};
*/

/*
static_assert(
  sizeof(sym::Type) == 16 || sizeof(sym::Type) == 12,
  "type size expectations failed"
);
*/
