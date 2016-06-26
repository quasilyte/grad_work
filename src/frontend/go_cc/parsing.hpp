#pragma once

namespace ast {
  struct Node;
}

namespace go_cc {
  class Reader;
  ast::Node* parse(Reader* reader);
}
