#pragma once

#include "typedefs.hpp"
#include <limits>

namespace sym {
  class Type;
}

class sym::Type {
public:
  typedef i32 Id;

  // Builtin type ids
  static const Id VOID_ID = std::numeric_limits<Id>::max();
  static const Id END_ARITH_ID = std::numeric_limits<Id>::max() - 1;
  static const Id ANY_ID = std::numeric_limits<Id>::max() - 2;
  static const Id NUM_ID = std::numeric_limits<Id>::max() - 3;
  static const Id REAL_ID = std::numeric_limits<Id>::max() - 4;
  static const Id INT_ID = std::numeric_limits<Id>::max() - 5;
  static const Id UNKNOWN_ID = std::numeric_limits<Id>::max() - 6;
  static const Id BEGIN_ARITH_ID = std::numeric_limits<Id>::max() - 7;
  static const Id STR_ID = std::numeric_limits<Id>::max() - 8;
  static const Id SYM_ID = std::numeric_limits<Id>::max() - 9;
  static const Id END_STRUCT_ID = std::numeric_limits<Id>::max() - 10;

  Type();
  Type(const Type&);
  Type(Id Tag);

  static Type* Void() noexcept;
  static Type* Any() noexcept;
  static Type* Num() noexcept;
  static Type* Real() noexcept;
  static Type* Int() noexcept;
  static Type* Unknown() noexcept;
  static Type* Str() noexcept;
  static Type* Sym() noexcept;

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

  Type* ExtendedWith(Type*);

  bool CompatibleWith(Type*) const noexcept;
  bool SameAs(Type*) const noexcept;

private:
  Id tag;

  // Builtin type identities
  static Type VOID;
  static Type ANY;
  static Type NUM;
  static Type REAL;
  static Type INT;
  static Type UNKNOWN;
  static Type STR;
  static Type SYM;
};
