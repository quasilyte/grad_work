#include "backend/cpp/cg/translator.hpp"

#include "backend/cpp/cg/code_writer.hpp"
#include "dbg/sym.hpp"
#include "backend/cpp/cg/type_map.hpp"
#include "backend/cpp/cg/utils.hpp"
#include "ast/defs.hpp"
#include "di/output.hpp"
#include "io/file_writer.hpp"
#include "di/unit.hpp"

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
    module_writer()("struct ")(struct_name)('{');
    for (sym::Param attr : s->attrs) {
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
