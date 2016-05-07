#pragma once

#include "io/file_writer.hpp"
#include "sym/type.hpp"

namespace ast {
  struct Node;
}

struct ast::Node {
  class TypeError{};

  Node();
  Node(sym::Type);

  virtual void generate_code(io::FileWriter*) = 0;

  const sym::Type& get_type() const noexcept;

protected:
  sym::Type type;
};

