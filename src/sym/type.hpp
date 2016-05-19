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

  bool CompatibleWith(Type) const noexcept;
  bool SameAs(Type) const noexcept;

private:
  Id tag;
};
