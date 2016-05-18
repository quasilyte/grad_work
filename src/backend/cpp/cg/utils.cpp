#include "backend/cpp/cg/utils.hpp"

#include "backend/cpp/cg/type_map.hpp"
#include "io/file_writer.hpp"
#include "sym/module.hpp"

using namespace io;
using namespace sym;

void cpp_cg::write_type(const Module* mod, Type ty, const FileWriter* fw) {
  if (ty.IsStruct()) {
    fw->Write("struct ", 7);
    fw->Write(mod->Struct(ty.Tag())->name);
  } else {
    fw->Write(type_name(ty));
  }
}
