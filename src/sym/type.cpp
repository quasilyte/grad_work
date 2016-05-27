#include "sym/type.hpp"
#include "sym/sym.hpp"

using namespace sym;

Type Type::Void() { return Type{VOID}; }
Type Type::Any() { return Type{ANY}; }
Type Type::Real() { return Type{REAL}; }
Type Type::Int() { return Type{INT}; }
Type Type::Unknown() { return Type{UNKNOWN}; }
Type Type::Str() { return Type{STR}; }
Type Type::Sym() { return Type{SYM}; }

Type Type::UnnamedFn(TypeId id) {
  return Type{UNNAMED_FN, id};
}

Type Type::DynDispatcher(TypeId id) {
  return Type{DYN_DISPATCHER, id};
}

Type Type::Struct(TypeId id) {
  return Type{STRUCT, id};
}

Type Type::Intrinsic(TypeId id) {
  return Type{INTRINSIC, id};
}

/*
TypeId Type::DynDispatcherTag(uint idx) { return idx + BEGIN_DYN_DISPATCHER + 1; }
int Type::DynDispatcherKey(TypeId id) { return id - BEGIN_DYN_DISPATCHER - 1; }
TypeId Type::LambdaTag(uint idx) { return idx + END_INTRINSIC; }
int Type::LambdaKey(TypeId id) { return id - END_INTRINSIC; }
TypeId Type::StructTag(uint idx) { return idx + 1; }
int Type::StructKey(TypeId id) { return id - 1; }
*/

Type::Type(): Type{VOID} {}
Type::Type(const Type& other): tag{other.tag}, id{other.id} {}
Type::Type(uint tag): tag{tag}, id{0} {}
Type::Type(uint tag, TypeId id): tag{tag}, id{id} {}

uint Type::Tag() const noexcept { return tag; }
TypeId Type::Id() const noexcept { return id; }

bool Type::IsVoid() const noexcept { return tag == VOID; }
bool Type::IsAny() const noexcept { return tag == ANY; }
bool Type::IsInt() const noexcept { return tag == INT; }
bool Type::IsUnknown() const noexcept { return tag == UNKNOWN; }
bool Type::IsReal() const noexcept { return tag == REAL; }
bool Type::IsStr() const noexcept { return tag == STR; }
bool Type::IsSym() const noexcept { return tag == SYM; }
bool Type::IsIntrinsic() const noexcept { return tag == INTRINSIC; }
bool Type::IsUnnamedFn() const noexcept { return tag == UNNAMED_FN; }
bool Type::IsNamedFn() const noexcept { return tag == NAMED_FN; }
bool Type::IsStruct() const noexcept { return tag == STRUCT; }
bool Type::IsDynDispatcher() const noexcept { return tag == DYN_DISPATCHER; }

bool Type::IsFn() const noexcept {
  return IsNamedFn() || IsUnnamedFn() || IsIntrinsic();
}

bool Type::IsArith() const noexcept {
  return IsReal() || IsInt();
}

Type Type::ExtendedWith(Type other) {
  if (IsUnknown()) {
    return other;
  }
  if (other.IsUnknown()) {
    return *this;
  }

  if (SameAs(other)) {
    return other;
  }

  return Type::Any();
}

bool Type::CompatibleWith(Type other) const noexcept {
  if (SameAs(other)
      || (IsArith() && other.IsArith())
      || (IsAny() || other.IsAny())) {
    return true;
  }

  return false;
}

bool Type::SameAs(Type other) const noexcept {
  return tag == other.tag;
}

bool Type::operator<(const Type& other) const {
  return tag < other.tag;
}

bool Type::operator==(const Type& other) const {
  return SameAs(other);
}
