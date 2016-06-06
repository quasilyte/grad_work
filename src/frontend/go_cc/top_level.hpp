#pragma once

#include "frontend/go_cc/decl.hpp"
#include <deps/cxx/vector.hpp>

namespace ast {
  struct DefVar;
}

namespace go_cc {
  struct TopLevel;
}

struct go_cc::TopLevel {
  std::vector<go_cc::TypedDecl> typed_globals;
  std::vector<go_cc::Decl> globals;
  std::vector<go_cc::FnDecl> fns;
  std::vector<go_cc::StructDecl> structs;
};
