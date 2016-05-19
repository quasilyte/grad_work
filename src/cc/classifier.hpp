#pragma once

#include "cc/top_level.hpp"

namespace cc {
  class Classifier;
}

class cc::Classifier {
public:
  static TopLevel Run(const char* input_cstr);
  static TopLevel Run(const char* input, usize input_len);

private:
  lex::TokenStream toks;
  TopLevel result;

  Classifier(const char* input_cstr);
  Classifier(const char* input, usize input_len);

  TopLevel Classify();

  void ClassifyDirective(const lex::Token& directive);
  void ClassifyFn(lex::TokenStream&);
  void ClassifyVar(lex::TokenStream&);
  void ClassifyStruct(lex::TokenStream&);
};

