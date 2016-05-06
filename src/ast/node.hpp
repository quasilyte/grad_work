#pragma once

#include "io/file_writer.hpp"

namespace ast {
  struct Node;
}

struct ast::Node {
  class TypeError{};

  Node() = default;
  Node(int type);

  virtual void generate_code(io::FileWriter*) = 0;

  int get_type() const noexcept;
  virtual const char* get_type_name() const;

protected:
  int type;
};

