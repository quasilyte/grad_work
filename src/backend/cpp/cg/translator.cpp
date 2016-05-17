#include "backend/cpp/cg/translator.hpp"

#include "backend/cpp/cg/code_writer.hpp"
#include "dbg/sym.hpp"
#include "backend/cpp/cg/type_map.hpp"
#include "ast/defs.hpp"

using namespace cpp_cg;

void Translator::Run(const cc::TranslationUnit &input, const io::FileWriter &output) {
  Translator self{input, output};
  self.Translate();
}

Translator::Translator(const cc::TranslationUnit& tu, const io::FileWriter& fw):
tu{tu}, fw{fw} {}

void Translator::Translate() {
  for (dt::StrView struct_name : tu.structs) {
    sym::Struct* s = tu.module.Struct(struct_name);
    fw.Write("struct ", 7);
    fw.Write(struct_name);
    fw.Write('{');
    for (sym::Param attr : s->attrs) {
      fw.Write(type_name(&attr.type));
      fw.Write(' ');
      fw.Write(attr.name);
      fw.Write(';');
    }
    fw.Write("};\n", 3);
  }

  for (ast::DefVar* global : tu.globals) {
    CodeWriter::Run(global, tu.module, fw);
    fw.Write('\n');
  }

  for (dt::StrView func_name : tu.funcs) {
    auto func = tu.module.Func(func_name);

    auto params = func->Params();
    fw.Write(type_name(&func->ret_type));
    fw.Write(' ');
    fw.Write(func_name);
    fw.Write('(');
    for (uint i = 0; i < params.size() - 1; ++i) {
      fw.Write(type_name(&params[i].type));
      fw.Write(' ');
      fw.Write(params[i].name);
      fw.Write(',');
    }
    fw.Write(type_name(&params.back().type));
    fw.Write(' ');
    fw.Write(params.back().name);
    fw.Write("){return ", 9);
    CodeWriter::Run(func->expr, tu.module, fw);
    fw.Write(';');
    fw.Write("}\n", 2);
  }

  for (ast::Node* expr : tu.exprs) {
    CodeWriter::Run(expr, tu.module, fw);
    fw.Write('\n');
  }
}
