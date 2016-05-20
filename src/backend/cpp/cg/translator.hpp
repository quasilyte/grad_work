#pragma once

#include "cc/translation_unit.hpp"
#include "io/file_writer.hpp"

namespace cpp_cg {
  class Translator;
  struct FileWriter;
}

class cpp_cg::Translator {
public:
  static void Run(
    const cc::TranslationUnit& input,
    const cpp_cg::FileWriter& output
  );

private:
  const cc::TranslationUnit& tu;
  const cpp_cg::FileWriter& fw;

  Translator(const cc::TranslationUnit&, const cpp_cg::FileWriter&);

  void Translate();
};
