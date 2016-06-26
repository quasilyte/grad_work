project(io)

set(
  io_src
  w_utils.cpp
  r_utils.cpp
  file_writer.cpp
)

add_library(io STATIC ${io_src})
