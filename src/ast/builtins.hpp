#pragma once

#include "ast/node.hpp"
#include <vector>

namespace ast {
  struct Sum;
}

struct ast::Sum: public Node {
  Sum(std::vector<Node*>);
  void GenerateCode(const sym::Module&, const io::FileWriter&) override;
  const sym::Type& Type() override;
  std::vector<Node*> operands;
};
