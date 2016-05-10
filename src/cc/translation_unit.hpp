#pragma once

#include "sym/module.hpp"
#include <vector>

namespace ast {
  class Node;
}

namespace cc {
  struct TranslationUnit;
}

struct cc::TranslationUnit {
  std::vector<dt::StrView> globals;
  std::vector<ast::Node*> exprs;

  sym::Module module;

  /*std::vector<ast::Node*> vars;
  std::vector<ast::Node*> tree;
  const sym::Module* module;*/
};
