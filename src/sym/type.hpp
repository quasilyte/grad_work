#pragma once

#include "typedefs.hpp"
#include <limits>

namespace sym {
  class Type;
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
  typedef i32 Id;

  enum: Id {
    // Never forget to increase this constant int literal.
    // If you will forget, compiler error will rise anyway (overflow).
    END_STRUCT = std::numeric_limits<Id>::max() - 11,
    SYM,
    STR,
    BEGIN_ARITH,
    UNKNOWN,
    INT,
    REAL,
    NUM,
    ANY,
    END_ARITH,
    LAMBDA,
    VOID,
  };

  enum: Id {
    // (num x)
    ANY_TO_NUM = std::numeric_limits<Id>::min(),
    REAL_TO_NUM,
    INT_TO_NUM,
    // (real x)
    ANY_TO_REAL,
    NUM_TO_REAL,
    INT_TO_REAL,
    // (int x)
    ANY_TO_INT ,
    NUM_TO_INT,
    REAL_TO_INT,

    END_INTRINSIC
  };

  static const Id BEGIN_STRUCT = 0;

  static Type Void();
  static Type Any();
  static Type Num();
  static Type Real();
  static Type Int();
  static Type Unknown();
  static Type Str();
  static Type Sym();
  static Type Lambda();

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
  bool IsLambda() const noexcept;

  bool IsIntrinsic() const noexcept;
  bool IsFunc() const noexcept;
  bool IsArith() const noexcept;
  bool IsStruct() const noexcept;

  Type ExtendedWith(Type);

  bool CompatibleWith(Type) const noexcept;
  bool SameAs(Type) const noexcept;

  bool operator<(const Type&) const;
  bool operator==(const Type&) const;

private:
  Id tag;
};
