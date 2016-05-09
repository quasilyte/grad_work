project(io)

set(
  io_src
  file_writer.cpp
  utils.cpp
)

add_library(io STATIC ${io_src})
