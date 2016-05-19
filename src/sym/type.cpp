#include "sym/type.hpp"

using namespace sym;

Type Type::VOID{Type::VOID_ID};
Type Type::ANY{Type::ANY_ID};
Type Type::NUM{Type::NUM_ID};
Type Type::REAL{Type::REAL_ID};
Type Type::INT{Type::INT_ID};
Type Type::UNKNOWN{Type::UNKNOWN_ID};
Type Type::STR{Type::STR_ID};
Type Type::SYM{Type::SYM_ID};

Type* Type::Void() noexcept { return &VOID; }
Type* Type::Any() noexcept { return &ANY; }
Type* Type::Num() noexcept { return &NUM; }
Type* Type::Real() noexcept { return &REAL; }
Type* Type::Int() noexcept { return &INT; }
Type* Type::Unknown() noexcept { return &UNKNOWN; }
Type* Type::Str() noexcept { return &STR; }
Type* Type::Sym() noexcept { return &SYM; }

Type::Type(): Type(VOID) {}
Type::Type(const Type& other): tag{other.tag} {}
Type::Type(Id tag): tag{tag} {}

Type::Id Type::Tag() const noexcept {
  return tag;
}

bool Type::IsVoid() const noexcept { return tag == VOID_ID; }
bool Type::IsAny() const noexcept { return tag == ANY_ID; }
bool Type::IsInt() const noexcept { return tag == INT_ID; }
bool Type::IsUnknown() const noexcept { return tag == UNKNOWN_ID; }
bool Type::IsReal() const noexcept { return tag == REAL_ID; }
bool Type::IsNum() const noexcept { return tag == NUM_ID; }
bool Type::IsStr() const noexcept { return tag == STR_ID; }
bool Type::IsSym() const noexcept { return tag == SYM_ID; }

bool Type::IsArith() const noexcept {
  return tag > BEGIN_ARITH_ID && tag < END_ARITH_ID;
}

bool Type::IsStruct() const noexcept {
  return tag < END_STRUCT_ID;
}

// Merge rules:
// A + A -> A
// int + real -> num
// A + B -> either<A, B>
// either<A, B> + C -> any
// either<A, B> + A -> either<A, B>
// A + any -> any
// A + parent_of(A) -> parent_of(A)
Type* Type::ExtendedWith(Type* other) {
  // No need to extend
  if (SameAs(other)) {
    return other;
  }

  // Nothing can extend Any
  if (IsAny() || other->IsAny()) {
    return Type::Any();
  }

  // !Any & not same arith types => promote to Num
  if (IsArith() || other->IsArith()) {
    return Type::Num();
  }

  // #FIXME: handle either<A, B>

  return Type::Any();
}

bool Type::CompatibleWith(Type* other) const noexcept {
  if (SameAs(other)
      || (IsArith() && other->IsArith())
      || (IsAny() || other->IsAny())) {
    return true;
  }

  return false;
}

bool Type::SameAs(Type* other) const noexcept {
  return tag == other->tag;
}

