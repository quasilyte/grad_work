#include "sym/type.hpp"

using namespace sym;

Type Type::Void() { return Type{VOID}; }
Type Type::Any() { return Type{ANY}; }
Type Type::Num() { return Type{NUM}; }
Type Type::Real() { return Type{REAL}; }
Type Type::Int() { return Type{INT}; }
Type Type::Unknown() { return Type{UNKNOWN}; }
Type Type::Str() { return Type{STR}; }
Type Type::Sym() { return Type{SYM}; }
Type Type::Lambda() { return Type{LAMBDA}; }

Type::Type(): Type(VOID) {}
Type::Type(const Type& other): tag{other.tag} {}
Type::Type(Id tag): tag{tag} {}

Type::Id Type::Tag() const noexcept {
  return tag;
}

bool Type::IsVoid() const noexcept { return tag == VOID; }
bool Type::IsAny() const noexcept { return tag == ANY; }
bool Type::IsInt() const noexcept { return tag == INT; }
bool Type::IsUnknown() const noexcept { return tag == UNKNOWN; }
bool Type::IsReal() const noexcept { return tag == REAL; }
bool Type::IsNum() const noexcept { return tag == NUM; }
bool Type::IsStr() const noexcept { return tag == STR; }
bool Type::IsSym() const noexcept { return tag == SYM; }
bool Type::IsLambda() const noexcept {return tag == LAMBDA; }

bool Type::IsIntrinsic() const noexcept {
  return tag < END_INTRINSIC;
}

bool Type::IsFunc() const noexcept {
  return tag <= 0;
}

bool Type::IsArith() const noexcept {
  return tag > BEGIN_ARITH && tag < END_ARITH;
}

bool Type::IsStruct() const noexcept {
  return tag > BEGIN_STRUCT && tag < END_STRUCT;
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
  // No need to extend
  if (SameAs(other)) {
    return other;
  }

  // Nothing can extend Any
  if (IsAny() || other.IsAny()) {
    return Type::Any();
  }

  // !Any & not same arith types => promote to Num
  if (IsArith() || other.IsArith()) {
    return Type::Num();
  }

  // #FIXME: handle classes
  // #FIXME: handle either<A, B>

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
