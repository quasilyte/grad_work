#pragma once

#include <frontend/go_cc/pods/top_level.hpp>
#include <frontend/go_cc/common/reader.hpp>

namespace go_cc {
  class Parser;
}

class go_cc::Parser {
public:
  static void Run(const go_cc::TopLevel&);

private:
  const go_cc::TopLevel& top;

  Parser(const go_cc::TopLevel&);

  void Parse();
};
