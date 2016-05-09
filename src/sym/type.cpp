#include "sym/type.hpp"

using namespace sym;
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
