#pragma once

#include "sym/module.hpp"
#include "sym/struct.hpp"
#include <vector>

namespace ast {
  struct Node;
  struct DefVar;
  struct DefFunc;
}

namespace cc {
  struct TranslationUnit;
}

struct cc::TranslationUnit {
  std::vector<dt::StrView> structs;
  std::vector<ast::DefVar*> globals;
  std::vector<ast::Node*> exprs;

  sym::Module module;
};
