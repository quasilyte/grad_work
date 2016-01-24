project(Resembler)
cmake_minimum_required(VERSION 2.8)

## Project-wide settings
enable_testing()
# We are currently using GCC only;
# -Wsign-conversion can be useful, but it is so annoying!
set(
  gcc_warn_flags
  "-pedantic \
   -Wextra \
   -Wextra \
   -Wcast-align \
   -Wcast-qual \
   -Wformat=2 \
   -Winit-self \
   -Wlogical-op \
   -Wmissing-declarations \
   -Wmissing-include-dirs \
   -Wredundant-decls \
   -Wshadow \
   -Wstrict-overflow=5 \
   -Wswitch-default \
   -Wundef \
   -Werror \
   -Wno-unused \
   -Wfatal-errors \
   -Wnoexcept \
   -Wold-style-cast \
   -Woverloaded-virtual \
   -Wsign-promo \
   -Wstrict-null-sentinel"
)
set(project_flags "-std=c++14")
set(
  CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${project_flags} ${gcc_warn_flags}"
)

include_directories(inc)

## Hack to make QtCreator show headers inside project window
file(GLOB_RECURSE header_files "inc/*.hpp")
add_custom_target(headers SOURCES ${header_files})

## Modules
add_subdirectory(test/lexer)
add_subdirectory(src/dbg)

## Main executable (mostly for debug purposes)
set(main_src main.cpp)
add_executable(${PROJECT_NAME} ${main_src})
target_link_libraries(${PROJECT_NAME} dbg)
