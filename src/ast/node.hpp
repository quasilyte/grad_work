#pragma once

#include "io/file_writer.hpp"
#include "sym/type.hpp"
#include "sym/module.hpp"

namespace ast {
  struct Node;
}

struct ast::Node {
  class TypeError{};

  virtual void GenerateCode(const sym::Module&, const io::FileWriter&) = 0;

  virtual const sym::Type& Type();
};

