#pragma once

#include "frontend/go_cc/decl.hpp"
#include <vector>

namespace ast {
  struct DefVar;
}

namespace go_cc {
  struct TopLevel;
}

struct go_cc::TopLevel {
  // std::vector<lex::Token> exprs;
  // std::vector<lex::TokenStream> funcs;
  std::vector<go_cc::TypedDecl> typed_globals;
  std::vector<go_cc::Decl> globals;
  std::vector<go_cc::FnDecl> fns;
  // std::vector<lex::TokenStream> structs;
};
