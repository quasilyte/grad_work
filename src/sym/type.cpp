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

TypeId Type::DynDispatcherTag(uint idx) { return idx + BEGIN_DYN_DISPATCHER + 1; }
int Type::DynDispatcherKey(TypeId id) { return id - BEGIN_DYN_DISPATCHER - 1; }
TypeId Type::LambdaTag(uint idx) { return idx + END_INTRINSIC; }
int Type::LambdaKey(TypeId id) { return id - END_INTRINSIC; }
TypeId Type::StructTag(uint idx) { return idx + 1; }
int Type::StructKey(TypeId id) { return id - 1; }

Type::Type(): Type(VOID) {}
Type::Type(const Type& other): tag{other.tag} {}
Type::Type(TypeId tag): tag{tag} {}

TypeId Type::Tag() const noexcept {
  return tag;
}

bool Type::IsVoid() const noexcept { return tag == VOID; }
bool Type::IsAny() const noexcept { return tag == ANY; }
bool Type::IsInt() const noexcept { return tag == INT; }
bool Type::IsUnknown() const noexcept { return tag == UNKNOWN; }
bool Type::IsReal() const noexcept { return tag == REAL; }
bool Type::IsStr() const noexcept { return tag == STR; }
bool Type::IsSym() const noexcept { return tag == SYM; }

bool Type::IsIntrinsic() const noexcept {
  return tag < END_INTRINSIC;
}

bool Type::IsLambda() const noexcept {
  return tag >= END_INTRINSIC
      && tag < (END_INTRINSIC + sym::MAX_UNIQ_SUFFIXES);
}

bool Type::IsFunc() const noexcept {
  return tag <= 0 && tag >= END_INTRINSIC;
}

bool Type::IsArith() const noexcept {
  return IsReal() || IsInt();
}

bool Type::IsStruct() const noexcept {
  return tag > BEGIN_STRUCT && tag < END_STRUCT;
}

bool Type::IsDynDispatcher() const noexcept {
  return tag > BEGIN_DYN_DISPATCHER && tag < END_DYN_DISPATCHER;
}

// Merge rules:
// A + A -> A
// int + real -> num
// A + B -> either<A, B>
// either<A, B> + C -> any
// either<A, B> + A -> either<A, B>
// A + any -> any
// A + parent_of(A) -> parent_of(A)
Type Type::ExtendedWith(Type other) {
  if (IsUnknown()) {
    return other;
  }
  if (other.IsUnknown()) {
    return *this;
  }

  // No need to extend
  if (SameAs(other)) {
    return other;
  }

  // Nothing can extend Any
  if (IsAny() || other.IsAny()) {
    return Type::Any();
  }

  // #FIXME: handle structs

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
