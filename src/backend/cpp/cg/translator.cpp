#include "backend/cpp/cg/translator.hpp"

#include "backend/cpp/cg/visitor.hpp"
#include "dbg/sym.hpp"
#include "backend/cpp/cg/type_map.hpp"

using namespace cpp_cg;

void Translator::Run(const cc::TranslationUnit &input, const io::FileWriter &output) {
  Translator self{input, output};
  self.Translate();
}

Translator::Translator(const cc::TranslationUnit& tu, const io::FileWriter& fw):
tu{tu}, fw{fw} {}

void Translator::Translate() {
  for (uint i = 0; i < tu.globals.size(); ++i) {
    auto ty = tu.module.Global(tu.globals[i]);

    fw.Write(type_name(ty));
    fw.Write(' ');
    fw.Write(tu.globals[i]);
    fw.Write('{');
    Visitor::Run(tu.exprs[i], fw);
    fw.Write("};", 2);
    fw.Write('\n');
  }

  for (uint i = tu.globals.size(); i < tu.exprs.size(); ++i) {
    Visitor::Run(tu.exprs[i], fw);
    fw.Write('\n');
  }
}
