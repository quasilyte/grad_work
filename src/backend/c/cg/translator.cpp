#include "backend/c/cg/translator.hpp"

#include "backend/c/cg/code_writer.hpp"
#include "dbg/sym.hpp"
#include "backend/c/cg/type_map.hpp"
#include "backend/c/cg/utils.hpp"
#include "ast/defs.hpp"
#include "di/pipe.hpp"
#include "io/file_writer.hpp"
#include "unit/fns.hpp"
#include "unit/structs.hpp"
#include "unit/globals.hpp"
#include "backend/c/cg/state.hpp"

using namespace c_cg;
using namespace di;

void Translator::Run() {
  Translator self{};
  self.Translate();
}

void Translator::Translate() {
  set_pipe(module_fw);

  for (uint i = 0; i < unit::global_count(); ++i) {
    sym::Global* glob = unit::get_global(i);
    write_type(glob->type);
    get_pipe()(' ')(glob->name)(";\n");
    /*
    get_pipe()('=');
    CodeWriter::Run(glob->val);
    get_pipe()(";\n");*/
  }

  get_pipe()("void init(){");
  for (uint i = 0; i < unit::global_count(); ++i) {
    sym::Global* glob = unit::get_global(i);

    get_pipe()(glob->name)('=');
    CodeWriter::Run(glob->val);
    get_pipe()(';');
  }
  get_pipe()("}\n");

  for (uint i = 0; i < unit::mono_fn_count(); ++i) {
    // sym::MonoFn* fn = ;
    CodeWriter::RunMonoFn(unit::get_mono_fn(i));
    get_pipe()('\n');
  }

  for (uint i = 0; i < unit::struct_count(); ++i) {
    sym::Struct* st = unit::get_struct(i);

    get_pipe()("struct ")(st->name)('{');
    for (sym::Param attr : st->attrs) {
      write_type(attr.type);
      get_pipe()(' ')(attr.name)(';');
    }
    get_pipe()("};\n");
  }

  /*
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

  */

  module_fw.Close();
  runtime_fw.Close();
}
