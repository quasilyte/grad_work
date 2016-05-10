#pragma once

#include "cc/translation_unit.hpp"
#include "io/file_writer.hpp"

namespace cpp_cg {
  class Translator;
}

class cpp_cg::Translator {
public:
  static void Run(
    const cc::TranslationUnit& input,
    const io::FileWriter& output = io::FileWriter{}
  );

private:
  const cc::TranslationUnit& tu;
  const io::FileWriter& fw;

  Translator(const cc::TranslationUnit&, const io::FileWriter&);

  void Translate();
};
