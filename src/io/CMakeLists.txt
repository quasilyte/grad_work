project(io)

set(
  io_src
  utils.cpp
  file_writer.cpp
)

add_library(io STATIC ${io_src})
