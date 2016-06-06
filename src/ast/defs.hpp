#pragma once

#include "ast/node.hpp"
#include "dt/str_view.hpp"
#include "sym/type.hpp"
#include "sym/param.hpp"
#include <deps/cxx/vector.hpp>

namespace ast {
  struct SetVar;
  struct SetAttr;
  struct DefVar;
  struct DefStruct;
}

struct ast::SetVar: public Node {
  SetVar(dt::StrView name, Node* value);

  void Accept(Visitor*) override;

  dt::StrView name;
  Node* value;
};

struct ast::SetAttr: public Node {
  SetAttr(dt::StrView obj_name, sym::Param* attr, Node* value);

  void Accept(Visitor*) override;

  dt::StrView obj_name;
  sym::Param* attr;
  Node* value;
};

struct ast::DefVar: public Node {
  DefVar(dt::StrView name, Node* value, sym::Type);

  void Accept(Visitor*) override;
  sym::Type Type() override;

  dt::StrView name;
  Node* value;
  sym::Type type;
};
