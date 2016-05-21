#include "backend/cpp/cg/translator.hpp"

#include "backend/cpp/cg/code_writer.hpp"
#include "dbg/sym.hpp"
#include "backend/cpp/cg/type_map.hpp"
#include "backend/cpp/cg/utils.hpp"
#include "ast/defs.hpp"
#include "backend/cpp/cg/file_writer.hpp"

using namespace cpp_cg;

void Translator::Run(const cc::TranslationUnit &input, const cpp_cg::FileWriter &output) {
  Translator self{input, output};
  self.Translate();
}

Translator::Translator(const cc::TranslationUnit& tu, const cpp_cg::FileWriter& fw):
tu{tu}, fw{fw} {}

void Translator::Translate() {
  for (dt::StrView struct_name : tu.structs) {
    sym::Struct* s = tu.module.Struct(struct_name);
    fw.module.Write("struct ", 7);
    fw.module.Write(struct_name);
    fw.module.Write('{');
    for (sym::Param attr : s->attrs) {
      write_type(&tu.module, attr.type, &fw.module);
      fw.module.Write(' ');
      fw.module.Write(attr.name);
      fw.module.Write(';');
    }
    fw.module.Write("};\n", 3);
  }

  for (ast::DefVar* global : tu.globals) {
    CodeWriter::Run(global, tu, fw);
    fw.module.Write('\n');
  }

  for (uint i = 0; i < tu.lambdas.size(); ++i) {
    sym::Lambda* lambda = tu.lambdas[i];
    auto params = lambda->Params();
    auto exprs = lambda->exprs;

    write_type(&tu.module, lambda->ret_type, &fw.module);
    fw.module.Write(' ');
    write_lambda_name(lambda, &fw.module);
    fw.module.Write('(');
    if (lambda->params.size()) {
      for (uint i = 0; i < params.size() - 1; ++i) {
        write_type(&tu.module, params[i].type, &fw.module);
        fw.module.Write(' ');
        fw.module.Write(params[i].name);
        fw.module.Write(',');
      }
      write_type(&tu.module, params.back().type, &fw.module);
      fw.module.Write(' ');
      fw.module.Write(params.back().name);
    } else {
      fw.module.Write("void", 4);
    }
    fw.module.Write("){", 2);

    for (uint i = 0; i < exprs.size() - 1; ++i) {
      CodeWriter::Run(exprs[i], tu, fw);
      fw.module.Write(';');
    }
    fw.module.Write("return ", 7);
    CodeWriter::Run(exprs.back(), tu, fw);
    fw.module.Write(';');

    fw.module.Write("}\n", 2);
  }

  for (auto multifunc_pair : tu.module.Funcs()) {
    auto funcs = multifunc_pair.second->funcs;

    for (auto& func_pair : funcs) {
      auto func = func_pair.second;
      auto params = func->Params();

      write_type(&tu.module, func->ret_type, &fw.module);
      fw.module.Write(' ');
      write_func_name(func, &fw.module);
      fw.module.Write('(');
      if (params.size()) {
        for (uint i = 0; i < params.size() - 1; ++i) {
          write_type(&tu.module, params[i].type, &fw.module);
          fw.module.Write(' ');
          fw.module.Write(params[i].name);
          fw.module.Write(',');
        }
        write_type(&tu.module, params.back().type, &fw.module);
        fw.module.Write(' ');
        fw.module.Write(params.back().name);
      } else {
        fw.module.Write("void", 4);
      }
      fw.module.Write("){", 2);

      for (uint i = 0; i < func->exprs.size() - 1; ++i) {
        CodeWriter::Run(func->exprs[i], tu, fw);
        fw.module.Write(';');
      }
      fw.module.Write("return ", 7);
      CodeWriter::Run(func->exprs.back(), tu, fw);
      fw.module.Write(';');
      fw.module.Write("}\n", 2);
    }
  }

  for (ast::Node* expr : tu.exprs) {
    CodeWriter::Run(expr, tu, fw);
    fw.module.Write('\n');
  }
}
