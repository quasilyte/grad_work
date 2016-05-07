#pragma once

#include "cc/parser.hpp"
#include "io/file_writer.hpp"

namespace cc {
  class CodeGen;
}

class cc::CodeGen {
public:
  CodeGen(const Parser::Tree&);

  void WriteTo(const io::FileWriter&);

private:
  const Parser::Tree& tree;
};
