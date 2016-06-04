#pragma once

#include "lex/cursor.hpp"
#include "frontend/go_cc/top_level.hpp"

namespace go_cc {
  class Classifier;
}

class go_cc::Classifier {
public:
  static TopLevel Run(const char* input_cstr);

private:
  lex::Cursor cur;
  TopLevel result;

  Classifier(const char* input_cstr);

  TopLevel Classify();

  void ClassifyVar();
  void ClassifyFn();

  // void ClassifyDirective(const lex::Token& directive);
  // void ClassifyFn(lex::TokenStream&);
  // void ClassifyVar(lex::TokenStream&);
  // void ClassifyStruct(lex::TokenStream&);
};
