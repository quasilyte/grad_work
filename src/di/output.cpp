#include "di/output.hpp"

#include "dev_assert.hpp"
#include "io/file_writer.hpp"
#include "app/api.hpp"

io::FileWriter module_fw;
io::FileWriter runtime_fw;

void di::set_files(FILE *module, FILE *runtime) {
  dev_assert(module != runtime);

  if (module && runtime) {
    module_fw.SetFile(module);
    runtime_fw.SetFile(runtime);
  } else {
    throw "module or runtime file is null";
  }

  app::push_shutdown_handler([]{
    module_fw.Close();
    runtime_fw.Close();
  });
}

io::FileWriter di::module_writer() {
  return module_fw;
}

io::FileWriter di::runtime_writer() {
  return runtime_fw;
}

