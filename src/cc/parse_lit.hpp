#pragma once

namespace ast {
  struct Node;
}

namespace lex {
  struct Cursor;
}

namespace cc {
  ast::Node* parse_num(lex::Cursor*);
  ast::Node* parse_str(lex::Cursor*);
}
