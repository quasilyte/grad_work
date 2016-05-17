#pragma once

#include "dt/alist.hpp"
#include "dt/hlist.hpp"
#include "sym/type.hpp"
#include <vector>

namespace sym {
  class Scope;
}

class sym::Scope {
public:
  void CreateLevel();
  void DropLevel();

  Type* DefineSymbol(const dt::StrView& key, Type val);

  Type* Symbol(const dt::StrView& key);
  Type* LocalSymbol(const dt::StrView& key);

private:
  struct Level {
    int h_syms = 0;
    int a_syms = 0;
    Level() = default;
  };

  std::vector<Level> levels;
  dt::Hlist<Type*> hlist;
  dt::Alist<Type*> alist;
};
