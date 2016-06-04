#pragma once

namespace ast {
  struct Node;
}

namespace lex {
  struct Cursor;
}

namespace go_cc {
  ast::Node* parse(lex::Cursor*);
}
