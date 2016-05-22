#include "backend/cpp/cg/translator.hpp"

#include "backend/cpp/cg/code_writer.hpp"
#include "dbg/sym.hpp"
#include "backend/cpp/cg/type_map.hpp"
#include "backend/cpp/cg/utils.hpp"
#include "ast/defs.hpp"
#include "di/output.hpp"
#include "io/file_writer.hpp"
#include "unit/fns.hpp"
#include "unit/structs.hpp"

using namespace cpp_cg;
using namespace di;

void Translator::Run(const cc::TranslationUnit &input) {
  Translator self{input};
  self.Translate();
}

Translator::Translator(const cc::TranslationUnit& tu): tu{tu} {}

void Translator::Translate() {
  for (uint i = 0; i < unit::struct_count(); ++i) {
    sym::Struct* st = unit::get_struct(i);

    module_writer()("struct ")(st->name)('{');
    for (sym::Param attr : st->attrs) {
      write_type(tu, attr.type);
      module_writer()(' ')(attr.name)(';');
    }
    module_writer()("};\n");
  }

  for (ast::DefVar* global : tu.globals) {
    CodeWriter::Run(global, tu);
    module_writer()('\n');
  }

  for (uint i = 0; i < unit::unnamed_fn_count(); ++i) {
    CodeWriter::RunLambda(unit::get_unnamed_fn(i), tu);
    module_writer()('\n');
  }

  for (uint i = 0; i < unit::named_fn_count(); ++i) {
    CodeWriter::RunFunc(unit::get_named_fn(i), tu);
    module_writer()('\n');
  }

  for (ast::Node* expr : tu.exprs) {
    CodeWriter::Run(expr, tu);
    module_writer()('\n');
  }
}
