#pragma once

#include <dt/alist.hpp>
#include <dt/hlist.hpp>
#include <sym/type.hpp>
#include <deps/cxx/vector.hpp>

namespace sym {
  class Scope;
}

// Note:
// Scope "leaks" resources because it leaves
// defined types on the free store even then they are
// not accessible from the hlist & alist.
// This is on purpose.
// We need to save those values for the code generator backend.
// Variables are bound to those pointers of types,
// this means that their type should exist until the end.
class sym::Scope {
public:
  void CreateLevel();
  void DropLevel();

  Type DefineSymbol(const dt::StrView& key, Type ty);

  Type Symbol(const dt::StrView& key);
  Type LocalSymbol(const dt::StrView& key);

  int LevelSize() const noexcept;

private:
  struct Level {
    int h_syms = 0;
    int a_syms = 0;
    Level() = default;
  };

  std::vector<Level> levels;
  dt::Hlist<Type> hlist;
  dt::Alist<Type> alist;
};
