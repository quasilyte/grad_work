#pragma once

#include "ast/node.hpp"
#include "lex/token.hpp"
#include "io/file_writer.hpp"

namespace ast {
  class Atom;
  class Int;
  class Real;
  class Str;
  struct Var;
}

class ast::Atom: public Node {
public:
  Atom(const char* data, u32 data_len);

  const char* Data() const noexcept;
  u32 Len() const noexcept;

protected:
  const char* data;
  u32 data_len;
};

static_assert(
  sizeof(ast::Atom) == 24 || sizeof(ast::Atom) == 12,
  "type size expectations failed"
);

class ast::Int: public Atom {
public:
  using Atom::Atom;

  void Accept(Visitor*);
};

class ast::Real: public Atom {
public:
  using Atom::Atom;

  void Accept(Visitor*);
};

class ast::Str: public Atom {
public:
  using Atom::Atom;

  void Accept(Visitor*);
};

struct ast::Var: public Node {
public:
  Var(const dt::StrView*, const sym::Type*);

  void Accept(Visitor*);

  const dt::StrView* name;
  const sym::Type* type;
};

static_assert(
  sizeof(ast::Var) == 24,
  "type size expectations failed"
);

