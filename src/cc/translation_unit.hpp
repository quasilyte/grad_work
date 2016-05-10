#pragma once

#include "ast/global_var.hpp"
#include <vector>

namespace ast {
  struct Node;
}

namespace sym {
  class Module;
}

namespace cc {
  struct TranslationUnit;
}

struct cc::TranslationUnit {
  std::vector<ast::GlobalVar> globals;
  std::vector<ast::Node*> exprs;

  /*std::vector<ast::Node*> vars;
  std::vector<ast::Node*> tree;
  const sym::Module* module;*/
};
