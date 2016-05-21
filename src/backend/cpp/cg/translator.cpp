#include "backend/cpp/cg/translator.hpp"

#include "backend/cpp/cg/code_writer.hpp"
#include "dbg/sym.hpp"
#include "backend/cpp/cg/type_map.hpp"
#include "backend/cpp/cg/utils.hpp"
#include "ast/defs.hpp"
#include "di/output.hpp"
#include "io/file_writer.hpp"

using namespace cpp_cg;
using namespace di;

void Translator::Run(const cc::TranslationUnit &input) {
  Translator self{input};
  self.Translate();
}

Translator::Translator(const cc::TranslationUnit& tu): tu{tu} {}

void Translator::Translate() {
  for (dt::StrView struct_name : tu.structs) {
    sym::Struct* s = tu.module.Struct(struct_name);
    module_writer()("struct ", 7)(struct_name)('{');
    for (sym::Param attr : s->attrs) {
      write_type(&tu.module, attr.type);
      module_writer()(' ')(attr.name)(';');
    }
    module_writer()("};\n", 3);
  }

  for (ast::DefVar* global : tu.globals) {
    CodeWriter::Run(global, tu);
    module_writer()('\n');
  }

  for (uint i = 0; i < tu.lambdas.size(); ++i) {
    sym::Lambda* lambda = tu.lambdas[i];
    auto params = lambda->Params();
    auto exprs = lambda->exprs;

    write_type(&tu.module, lambda->ret_type);
    module_writer()(' ');
    write_lambda_name(lambda);
    module_writer()('(');
    if (lambda->params.size()) {
      for (uint i = 0; i < params.size() - 1; ++i) {
        write_type(&tu.module, params[i].type);
        module_writer()(' ')(params[i].name)(',');
      }
      write_type(&tu.module, params.back().type);
      module_writer()(' ')(params.back().name);
    } else {
      module_writer()("void", 4);
    }
    module_writer()("){", 2);

    for (uint i = 0; i < exprs.size() - 1; ++i) {
      CodeWriter::Run(exprs[i], tu);
      module_writer()(';');
    }
    module_writer()("return ", 7);
    CodeWriter::Run(exprs.back(), tu);
    module_writer()(';');

    module_writer()("}\n", 2);
  }

  for (auto multifunc_pair : tu.module.Funcs()) {
    auto funcs = multifunc_pair.second->funcs;

    for (auto& func_pair : funcs) {
      auto func = func_pair.second;
      auto params = func->Params();

      write_type(&tu.module, func->ret_type);
      module_writer()(' ');
      write_func_name(func);
      module_writer()('(');
      if (params.size()) {
        for (uint i = 0; i < params.size() - 1; ++i) {
          write_type(&tu.module, params[i].type);
          module_writer()(' ')(params[i].name)(',');
        }
        write_type(&tu.module, params.back().type);
        module_writer()(' ')(params.back().name);
      } else {
        module_writer()("void", 4);
      }
      module_writer()("){", 2);

      for (uint i = 0; i < func->exprs.size() - 1; ++i) {
        CodeWriter::Run(func->exprs[i], tu);
        module_writer()(';');
      }
      module_writer()("return ", 7);
      CodeWriter::Run(func->exprs.back(), tu);
      module_writer()(';');
      module_writer()("}\n", 2);
    }
  }

  for (ast::Node* expr : tu.exprs) {
    CodeWriter::Run(expr, tu);
    module_writer()('\n');
  }
}
