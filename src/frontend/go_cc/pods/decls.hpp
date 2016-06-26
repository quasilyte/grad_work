#pragma once

#include <dt/str_view.hpp>
#include <sym/type.hpp>
#include <lex/token.hpp>

namespace go_cc {
  struct VarDecl;
  struct FnDecl;
  struct StructDecl;
}

struct go_cc::VarDecl {
  dt::StrView name;
  dt::StrView init;
  sym::Type type;
};

struct go_cc::FnDecl {
  dt::StrView name;
  dt::StrView params;
  dt::StrView body;
  sym::Type ret_type;
};

struct go_cc::StructDecl {
  dt::StrView name;
  dt::StrView body;
};
