#pragma once

#include <ast/node.hpp>
#include <dt/str_view.hpp>
#include <sym/type.hpp>
#include <ast/typedefs.hpp>

namespace ast {
  struct Atom;
  struct Int;
  struct Real;
  struct Str;
  struct CompoundLit;
}

struct ast::Atom: public Node {
  Atom(dt::StrView);

  dt::StrView datum;
};

static_assert(
  sizeof(ast::Atom) == 24 || sizeof(ast::Atom) == 12,
  "type size expectations failed"
);

#define GEN_ATOM(NAME) \
  struct ast::NAME: public Atom { \
    using Atom::Atom; \
    void Accept(Visitor*) override; \
    sym::Type Type() override; \
  }

GEN_ATOM(Int);
GEN_ATOM(Real);
GEN_ATOM(Str);

struct ast::CompoundLit: public Node {
  CompoundLit(ast::NodeList&&, sym::Type);

  void Accept(Visitor*) override;
  sym::Type Type() override;

  ast::NodeList initializers;
  sym::Type type;
};

#undef GEN_ATOM
