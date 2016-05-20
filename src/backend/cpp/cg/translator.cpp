#include "backend/cpp/cg/translator.hpp"

#include "backend/cpp/cg/code_writer.hpp"
#include "dbg/sym.hpp"
#include "backend/cpp/cg/type_map.hpp"
#include "backend/cpp/cg/utils.hpp"
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
      write_type(&tu.module, attr.type, &fw);
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

  for (auto multifunc_pair : tu.module.Funcs()) {
    auto funcs = multifunc_pair.second->funcs;
    for (auto& func_pair : funcs) {
      auto func = func_pair.second;
      auto params = func->Params();
      write_type(&tu.module, func->ret_type, &fw);
      fw.Write(' ');
      fw.Write(func->name);
      fw.Write('(');
      if (params.size()) {
        for (uint i = 0; i < params.size() - 1; ++i) {
          write_type(&tu.module, params[i].type, &fw);
          fw.Write(' ');
          fw.Write(params[i].name);
          fw.Write(',');
        }
        write_type(&tu.module, params.back().type, &fw);
        fw.Write(' ');
        fw.Write(params.back().name);
      } else {
        fw.Write("void", 4);
      }
      fw.Write("){", 2);

      for (uint i = 0; i < func->exprs.size() - 1; ++i) {
        CodeWriter::Run(func->exprs[i], tu.module, fw);
        fw.Write(';');
      }
      fw.Write("return ", 7);
      CodeWriter::Run(func->exprs.back(), tu.module, fw);
      fw.Write(';');
      fw.Write("}\n", 2);
    }
  }

  for (ast::Node* expr : tu.exprs) {
    CodeWriter::Run(expr, tu.module, fw);
    fw.Write('\n');
  }
}
