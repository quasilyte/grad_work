#pragma once

#include <io/file_writer.hpp>

namespace di {
  void set_pipe(io::FileWriter);
  io::FileWriter get_pipe();
}
