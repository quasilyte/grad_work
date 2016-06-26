#pragma once

namespace lex {
  class Reader;
}

namespace c_lex {
  struct Comment;
}

struct c_lex::Comment {
  static void Skip(lex::Reader*);
};
