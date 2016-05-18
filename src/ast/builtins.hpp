#pragma once

#include "ast/node.hpp"
#include "dt/str_view.hpp"
#include "sym/type.hpp"
#include "sym/param.hpp"
#include <vector>

namespace ast {
  struct Sum;
  struct FuncCall;
  struct AttrAccess;
}

struct ast::Sum: public Node {
  Sum(std::vector<Node*>&&);

  void Accept(Visitor*);

  std::vector<Node*> operands;
};

struct ast::FuncCall: public Node {
  FuncCall(dt::StrView name, std::vector<Node*>&& args, sym::Type);

  void Accept(Visitor*);

  dt::StrView name;
  std::vector<Node*> args;
  sym::Type ty;
};

// foo.bar
struct ast::AttrAccess: public Node {
  AttrAccess(dt::StrView, sym::Param*);

  void Accept(Visitor*);

  dt::StrView obj_name;
  sym::Param* attr;
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
