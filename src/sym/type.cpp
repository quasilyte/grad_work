#include "sym/type.hpp"

using namespace sym;
using namespace sym::flags;

Type Type::VOID{0, "void", 0};
Type Type::ANY{1, "any", ARITH};
Type Type::INT{2, "long", ARITH};
Type Type::REAL{3, "double", ARITH};
Type Type::NUM{4, "num", ARITH};
Type Type::STR{5, "str", 0};

// #FIXME: Should be removed!
Type::Type():
name{"void"}, id{0}, flags{0} {}

Type::Type(int id, const char* name, i32 flags):
name{name}, id{id}, flags{flags} {}

int Type::Id() const noexcept {
  return id;
}

i32 Type::Flags() const noexcept {
  return flags;
}

const char* Type::Name() const noexcept {
  return name;
}

bool Type::IsVoid() const noexcept { return id == VOID.id; }
bool Type::IsAny() const noexcept { return id == ANY.id; }
bool Type::IsInt() const noexcept { return id == INT.id; }
bool Type::IsReal() const noexcept { return id == REAL.id; }
bool Type::IsNum() const noexcept { return id == NUM.id; }
bool Type::IsStr() const noexcept { return id == STR.id; }

bool Type::Arith() const noexcept { return flags & ARITH; }
bool Type::Defined() const noexcept { return flags & DEFINED; }

void Type::MarkDefined() noexcept { flags |= DEFINED; }

// Merge rules:
// A + A -> A
// int + real -> num
// A + B -> either<A, B>
// either<A, B> + C -> any
// either<A, B> + A -> either<A, B>
// A + any -> any
// A + parent_of(A) -> parent_of(A)
const Type& Type::Merge(const Type& other) const noexcept {
  if (id == other.id) {
    return other;
  }

  if (Arith() && other.Arith()) {
    return sym::Type::NUM;
  }

  return sym::Type::ANY;
}

bool Type::CompatibleWith(const Type& other) const noexcept {
  if ((id == other.id)
      || (Arith() && other.Arith())
      || (IsAny() || other.IsAny())) {
    return true;
  }

  return false;
}
