#pragma once

#include "cc/parser.hpp"
#include "io/file_writer.hpp"

namespace cc {
  class CodeGen;
}

class cc::CodeGen {
public:
  CodeGen(const sym::Module&, const Parser::Tree&);

  void WriteTo(const io::FileWriter&);

private:
  const sym::Module& module;
  const Parser::Tree& tree;
};
