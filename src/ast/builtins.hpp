#pragma once

#include "ast/node.hpp"
#include <vector>

namespace ast {
  class Sum;
}

class ast::Sum: public Node {
public:
  Sum(std::vector<Node*>&&);

  const std::vector<Node*>& Operands() const noexcept;

  void Accept(Visitor*);

private:
  std::vector<Node*> operands;
};

/*
#include "ast/node.hpp"
#include "lex/token.hpp"
#include <vector>

namespace ast {
  struct FuncCall;
  struct Sum;
}

struct ast::FuncCall: public Node {
  FuncCall(const sym::Type*, lex::Token name, std::vector<Node*>&& args);
  void GenerateCode(const sym::Module*, const io::FileWriter&) override;
  const sym::Type* Type() override;
  const sym::Type* type;
  lex::Token name;
  std::vector<Node*> args;
};

struct ast::Sum: public Node {
  Sum(std::vector<Node*>&& operands);
  void GenerateCode(const sym::Module*, const io::FileWriter&) override;
  const sym::Type* Type() override;
  std::vector<Node*> operands;
};
*/
