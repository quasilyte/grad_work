#include "backend/cpp/cg/translator.hpp"

#include "backend/cpp/cg/code_writer.hpp"
#include "dbg/sym.hpp"
#include "backend/cpp/cg/type_map.hpp"
#include "backend/cpp/cg/utils.hpp"
#include "ast/defs.hpp"
#include "di/output.hpp"

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
    module_write("struct ", 7);
    module_write(struct_name);
    module_write('{');
    for (sym::Param attr : s->attrs) {
      write_type(&tu.module, attr.type);
      module_write(' ');
      module_write(attr.name);
      module_write(';');
    }
    module_write("};\n", 3);
  }

  for (ast::DefVar* global : tu.globals) {
    CodeWriter::Run(global, tu);
    module_write('\n');
  }

  for (uint i = 0; i < tu.lambdas.size(); ++i) {
    sym::Lambda* lambda = tu.lambdas[i];
    auto params = lambda->Params();
    auto exprs = lambda->exprs;

    write_type(&tu.module, lambda->ret_type);
    module_write(' ');
    write_lambda_name(lambda);
    module_write('(');
    if (lambda->params.size()) {
      for (uint i = 0; i < params.size() - 1; ++i) {
        write_type(&tu.module, params[i].type);
        module_write(' ');
        module_write(params[i].name);
        module_write(',');
      }
      write_type(&tu.module, params.back().type);
      module_write(' ');
      module_write(params.back().name);
    } else {
      module_write("void", 4);
    }
    module_write("){", 2);

    for (uint i = 0; i < exprs.size() - 1; ++i) {
      CodeWriter::Run(exprs[i], tu);
      module_write(';');
    }
    module_write("return ", 7);
    CodeWriter::Run(exprs.back(), tu);
    module_write(';');

    module_write("}\n", 2);
  }

  for (auto multifunc_pair : tu.module.Funcs()) {
    auto funcs = multifunc_pair.second->funcs;

    for (auto& func_pair : funcs) {
      auto func = func_pair.second;
      auto params = func->Params();

      write_type(&tu.module, func->ret_type);
      module_write(' ');
      write_func_name(func);
      module_write('(');
      if (params.size()) {
        for (uint i = 0; i < params.size() - 1; ++i) {
          write_type(&tu.module, params[i].type);
          module_write(' ');
          module_write(params[i].name);
          module_write(',');
        }
        write_type(&tu.module, params.back().type);
        module_write(' ');
        module_write(params.back().name);
      } else {
        module_write("void", 4);
      }
      module_write("){", 2);

      for (uint i = 0; i < func->exprs.size() - 1; ++i) {
        CodeWriter::Run(func->exprs[i], tu);
        module_write(';');
      }
      module_write("return ", 7);
      CodeWriter::Run(func->exprs.back(), tu);
      module_write(';');
      module_write("}\n", 2);
    }
  }

  for (ast::Node* expr : tu.exprs) {
    CodeWriter::Run(expr, tu);
    module_write('\n');
  }
}
