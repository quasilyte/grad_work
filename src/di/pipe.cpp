#include <di/pipe.hpp>

io::FileWriter pipe;

void di::set_pipe(io::FileWriter fw) {
  pipe = fw;
}

io::FileWriter di::get_pipe() {
  return pipe;
}
