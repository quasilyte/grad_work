#pragma once

#include <vector>

namespace ast {
  struct Node;
  struct DefVar;
}

namespace cc {
  struct TranslationUnit;
}

struct cc::TranslationUnit {
  std::vector<ast::DefVar*> globals;
  std::vector<ast::Node*> exprs;
};
