#include "backend/cpp/cg/translator.hpp"

#include "backend/cpp/cg/code_writer.hpp"
#include "dbg/sym.hpp"
#include "backend/cpp/cg/type_map.hpp"
#include "backend/cpp/cg/utils.hpp"
#include "ast/defs.hpp"
#include "di/pipe.hpp"
#include "io/file_writer.hpp"
#include "unit/fns.hpp"
#include "unit/structs.hpp"
#include "backend/cpp/cg/state.hpp"

using namespace cpp_cg;
using namespace di;

void Translator::Run(const cc::TranslationUnit &input) {
  Translator self{input};
  self.Translate();
}

Translator::Translator(const cc::TranslationUnit& tu): tu{tu} {}

void Translator::Translate() {
  set_pipe(module_fw);

  for (uint i = 0; i < unit::struct_count(); ++i) {
    sym::Struct* st = unit::get_struct(i);

    get_pipe()("struct ")(st->name)('{');
    for (sym::Param attr : st->attrs) {
      write_type(tu, attr.type);
      get_pipe()(' ')(attr.name)(';');
    }
    get_pipe()("};\n");
  }

  for (ast::DefVar* global : tu.globals) {
    CodeWriter::Run(global, tu);
    get_pipe()('\n');
  }

  for (uint i = 0; i < unit::unnamed_fn_count(); ++i) {
    CodeWriter::RunLambda(unit::get_unnamed_fn(i), tu);
    get_pipe()('\n');
  }

  for (uint i = 0; i < unit::named_fn_count(); ++i) {
    CodeWriter::RunFunc(unit::get_named_fn(i), tu);
    get_pipe()('\n');
  }

  for (ast::Node* expr : tu.exprs) {
    CodeWriter::Run(expr, tu);
    get_pipe()('\n');
  }

  module_fw.Close();
  runtime_fw.Close();
}
