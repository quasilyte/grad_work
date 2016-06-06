#pragma once

#include <deps/cxx/vector.hpp>

namespace ast {
  struct Node;

  typedef std::vector<ast::Node*> NodeList;
  typedef std::vector<ast::Node*> ArgList;
}
