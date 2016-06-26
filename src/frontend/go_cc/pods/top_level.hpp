#pragma once

#include <frontend/go_cc/pods/decls.hpp>
#include <deps/cxx/vector.hpp>

namespace ast {
  struct DefVar;
}

namespace go_cc {
  struct TopLevel;
}

struct go_cc::TopLevel {
  std::vector<go_cc::VarDecl> globals;
  std::vector<go_cc::FnDecl> fns;
  std::vector<go_cc::StructDecl> structs;
};
