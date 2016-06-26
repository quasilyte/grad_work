#pragma once

#include <frontend/go_cc/common/reader.hpp>
#include <frontend/go_cc/pods/top_level.hpp>

namespace go_cc {
  class Classifier;
}

class go_cc::Classifier {
public:
  static TopLevel Run(const char* input_cstr);

private:
  Reader reader;
  TopLevel result;

  Classifier(const char* input_cstr);

  TopLevel Classify();

  void ClassifyVar();
  void ClassifyFn();
  void ClassifyType();
};
