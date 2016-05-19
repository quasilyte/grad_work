#pragma once

#include "ast/node.hpp"
#include "io/file_writer.hpp"
#include "dt/str_view.hpp"
#include "sym/type.hpp"
#include <vector>

namespace ast {
  struct Atom;
  struct Int;
  struct Real;
  struct Str;
  struct Sym;
  // The structs below are not atoms and must be moved from this file:
  struct CompoundLiteral;
  struct Var;
}

struct ast::Atom: public Node {
  Atom(dt::StrView);

  dt::StrView datum;
};

static_assert(
  sizeof(ast::Atom) == 24 || sizeof(ast::Atom) == 12,
  "type size expectations failed"
);

struct ast::Int: public Atom {
  using Atom::Atom;
  void Accept(Visitor*);
};

struct ast::Real: public Atom {
  using Atom::Atom;
  void Accept(Visitor*);
};

struct ast::Str: public Atom {
  using Atom::Atom;
  void Accept(Visitor*);
};

struct ast::Sym: public Atom {
  using Atom::Atom;
  void Accept(Visitor*);
};

struct ast::Var: public Node {
  Var(dt::StrView, sym::Type);

  void Accept(Visitor*);

  const dt::StrView name;
  const sym::Type type;
};

struct ast::CompoundLiteral: public Node {
  CompoundLiteral(std::vector<Node*>&&, sym::Type);

  void Accept(Visitor*);

  std::vector<Node*> initializers;
  sym::Type type;
};

