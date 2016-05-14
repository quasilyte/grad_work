#include "sym/scope.hpp"

using namespace sym;

void Scope::CreateLevel() {
  levels.push_back(Level{});
}

void Scope::DropLevel() {
  Level level = levels.back();

  hlist.Drop(level.h_syms);
  alist.Drop(level.a_syms);

  levels.pop_back();
}

void Scope::DefineSymbol(const dt::StrView& key, Type* val) {
  auto& level = levels.back();

  if (key.Len() > 9) {
    level.a_syms += 1;
    alist.Insert(key, val);
  } else {
    level.h_syms += 1;
    hlist.Insert(key, val);
  }
}

Type* Scope::Symbol(const dt::StrView& key) {
  if (key.Len() > 9) {
    return alist.Find(key, alist.Size());
  } else {
    return hlist.Find(key, hlist.Size());
  }
}

Type* Scope::LocalSymbol(const dt::StrView& key) {
  auto level = levels.back();

  if (key.Len() > 9) {
    return alist.Find(key, level.a_syms);
  } else {
    return hlist.Find(key, level.h_syms);
  }
}
