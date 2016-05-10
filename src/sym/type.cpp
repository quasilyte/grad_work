#include "sym/type.hpp"

using namespace sym;

Type Type::Void() { return Type{VOID}; }
Type Type::Any() { return Type{ANY}; }
Type Type::Num() { return Type{NUM}; }
Type Type::Real() { return Type{REAL}; }
Type Type::Int() { return Type{INT}; }
Type Type::Str() { return Type{STR}; }

Type::Type(): Type(VOID) {}
Type::Type(enum Tag tag): tag{tag} {}

enum Type::Tag Type::Tag() const noexcept {
  return tag;
}

bool Type::IsVoid() const noexcept { return tag == VOID; }
bool Type::IsAny() const noexcept { return tag == ANY; }
bool Type::IsInt() const noexcept { return tag == INT; }
bool Type::IsReal() const noexcept { return tag == REAL; }
bool Type::IsNum() const noexcept { return tag == NUM; }
bool Type::IsStr() const noexcept { return tag == STR; }

bool Type::IsArith() const noexcept {
  return tag > BEGIN_ARITH && tag < END_ARITH;
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

void Type::ExtendWith(Type other) {
  tag = ExtendedWith(other).Tag();
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

/*
using namespace sym::flags;

const Type Type::VOID{"void"};
const Type Type::ANY{"any"};
const Type Type::INT{"long"};
const Type Type::REAL{"double"};
const Type Type::NUM{"num"};
const Type Type::STR{"str"};

Type::Type(const char* name): name{name} {}

const char* Type::Name() const noexcept {
  return name;
}

bool Type::IsVoid() const noexcept { return this == &VOID; }
bool Type::IsAny() const noexcept { return this == &ANY; }
bool Type::IsInt() const noexcept { return this == &INT; }
bool Type::IsReal() const noexcept { return this == &REAL; }
bool Type::IsNum() const noexcept { return this == &NUM; }
bool Type::IsStr() const noexcept { return this == &STR; }

bool Type::Arith() const noexcept {
  return IsInt()
      || IsReal()
      || IsNum()
      || IsAny();
}

// Merge rules:
// A + A -> A
// int + real -> num
// A + B -> either<A, B>
// either<A, B> + C -> any
// either<A, B> + A -> either<A, B>
// A + any -> any
// A + parent_of(A) -> parent_of(A)
const Type* Type::Merge(const Type* other) const noexcept {
  if (SameAs(other)) {
    return other;
  }

  if (Arith() && other->Arith()) {
    return &sym::Type::NUM;
  }

  return &sym::Type::ANY;
}

bool Type::CompatibleWith(const Type* other) const noexcept {
  if (SameAs(other)
      || (Arith() && other->Arith())
      || (IsAny() || other->IsAny())) {
    return true;
  }

  return false;
}

bool Type::SameAs(const Type* other) const noexcept {
  return this == other;
}
*/
