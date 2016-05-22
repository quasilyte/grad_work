#pragma once

#include "cc/translation_unit.hpp"

namespace cpp_cg {
  class Translator;
}

class cpp_cg::Translator {
public:
  static void Run(const cc::TranslationUnit& input);

private:
  const cc::TranslationUnit& tu;

  Translator(const cc::TranslationUnit&);

  void Translate();

  void WriteFunc();
};
