#pragma once

#include <typedefs.hpp>
#include <deps/cxx/limits.hpp>

namespace sym {
  class Type;
  typedef u32 TypeId;
}

class sym::Type {
public:
  static const int BITS_PER_TAG = 6;
  static const int BITS_PER_VAL = (sizeof(u32) * 8) - BITS_PER_TAG;

  // Any value should fit in BITS_PER_TAG bits
  enum: unsigned {
    VOID,
    UNKNOWN,
    ANY,
    REAL,
    INT,
    BOOL,
    STRUCT,
    SYM,
    STR,
    INTRINSIC,
    UNNAMED_FN,
    NAMED_FN,
    MONO_FN,
    DYN_DISPATCHER,
  };

  // Intrinsics TypeId
  enum: TypeId {
    // (real x)
    ANY_TO_REAL,
    INT_TO_REAL,
    // (int x)
    ANY_TO_INT,
    REAL_TO_INT,
    // (any x)
    INT_TO_ANY,
    REAL_TO_ANY,
  };

  static Type Void();
  static Type Any();
  static Type Real();
  static Type Int();
  static Type Bool();
  static Type Unknown();
  static Type Str();
  static Type Sym();

  static Type UnnamedFn(TypeId id);
  static Type MonoFn(TypeId id);
  static Type DynDispatcher(TypeId id);
  static Type Struct(TypeId id);
  static Type Intrinsic(TypeId id);

  /*
  static TypeId DynDispatcherTag(uint idx);
  static int DynDispatcherKey(TypeId);
  static TypeId LambdaTag(uint idx);
  static int LambdaKey(TypeId);
  static TypeId StructTag(uint idx);
  static int StructKey(TypeId);
  */

  Type();
  Type(const Type&);
  Type(uint Tag);
  Type(uint Tag, TypeId id);

  uint Tag() const noexcept;
  TypeId Id() const noexcept;

  bool IsVoid() const noexcept;
  bool IsAny() const noexcept;
  bool IsInt() const noexcept;
  bool IsBool() const noexcept;
  bool IsUnknown() const noexcept;
  bool IsReal() const noexcept;
  bool IsStr() const noexcept;
  bool IsSym() const noexcept;
  bool IsStruct() const noexcept;
  bool IsDynDispatcher() const noexcept;
  bool IsIntrinsic() const noexcept;
  bool IsUnnamedFn() const noexcept;
  bool IsMonoFn() const noexcept;
  bool IsNamedFn() const noexcept;

  bool IsFn() const noexcept;
  bool IsArith() const noexcept;

  Type ExtendedWith(Type);

  bool CompatibleWith(Type) const noexcept;
  bool SameAs(Type) const noexcept;

  bool operator<(const Type&) const;
  bool operator==(const Type&) const;

private:
  uint tag: BITS_PER_TAG;
  TypeId id: BITS_PER_VAL;
};

static_assert(
  sizeof(sym::Type) == sizeof(sym::TypeId),
  "type size expectations failed"
);
