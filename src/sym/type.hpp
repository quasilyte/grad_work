#pragma once

#include "typedefs.hpp"
#include <limits>

namespace sym {
  class Type;
  typedef i32 TypeId;
}

/**
  Type ladder:
  min(int): intrinsics ++
  max(int): builtin types --
  1..max(int)-count(builtin types): user defined types ++
  min(int)+count(intrinsics)..0: user defined functions --

  functions |     types
  [min]><[0]|[1]><[max]
*/

class sym::Type {
public:

  enum: TypeId {
    // Never forget to increase this constant int literal.
    // If you will forget, compiler error will rise anyway (overflow).
    END_STRUCT = std::numeric_limits<TypeId>::max() - 7,
    SYM,
    STR,
    UNKNOWN,
    INT,
    REAL,
    ANY,
    VOID,
  };

  enum: TypeId {
    // (real x)
    ANY_TO_REAL = std::numeric_limits<TypeId>::min(),
    INT_TO_REAL,
    // (int x)
    ANY_TO_INT ,
    REAL_TO_INT,

    END_INTRINSIC
  };

  static const TypeId BEGIN_STRUCT = 0;

  static Type Void();
  static Type Any();
  static Type Real();
  static Type Int();
  static Type Unknown();
  static Type Str();
  static Type Sym();

  static TypeId LambdaTag(uint idx);
  static int LambdaKey(TypeId);
  static TypeId StructTag(uint idx);
  static int StructKey(TypeId);

  Type();
  Type(const Type&);
  Type(TypeId Tag);

  TypeId Tag() const noexcept;

  bool IsVoid() const noexcept;
  bool IsAny() const noexcept;
  bool IsInt() const noexcept;
  bool IsUnknown() const noexcept;
  bool IsReal() const noexcept;
  bool IsStr() const noexcept;
  bool IsSym() const noexcept;

  bool IsIntrinsic() const noexcept;
  bool IsLambda() const noexcept;
  bool IsFunc() const noexcept;
  bool IsArith() const noexcept;
  bool IsStruct() const noexcept;

  Type ExtendedWith(Type);

  bool CompatibleWith(Type) const noexcept;
  bool SameAs(Type) const noexcept;

  bool operator<(const Type&) const;
  bool operator==(const Type&) const;

private:
  TypeId tag;
};
