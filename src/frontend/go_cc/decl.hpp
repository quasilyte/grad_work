#pragma once

#include "dt/str_view.hpp"
#include "sym/type.hpp"
#include "lex/token.hpp"

namespace go_cc {
  struct Decl;
  struct TypedDecl;
  struct FnDecl;
}

struct go_cc::Decl {
  dt::StrView name;
  dt::StrView init;
};

struct go_cc::TypedDecl {
  dt::StrView name;
  sym::Type type;
  dt::StrView init;
};

struct go_cc::FnDecl {
  dt::StrView name;
  dt::StrView params;
  dt::StrView body;
  sym::Type ret_type;
};
