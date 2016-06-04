#pragma once

namespace c_cg {
  class Translator;
}

class c_cg::Translator {
public:
  static void Run();

private:
  void Translate();

  void WriteFunc();
};
