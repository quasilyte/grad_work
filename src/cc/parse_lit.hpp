#pragma once

namespace ast {
  struct Node;
}

namespace lex {
  class Reader;
}

namespace cc {
  ast::Node* parse_num(lex::Reader*);
  ast::Node* parse_str(lex::Reader*);
}
