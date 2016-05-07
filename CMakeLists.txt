SET(CMAKE_C_COMPILER "/usr/bin/clang")
SET(CMAKE_CXX_COMPILER "/usr/bin/clang++")

project(Resembler)
cmake_minimum_required(VERSION 2.8)

## Project-wide settings

enable_testing()
# -Wsign-conversion can be useful, but it is so annoying!
# -Wshadow prohobits writing sane ctor signatures
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
set(
  clang_warn_flags
  "-Wall \
   -Wextra"
)
set(project_flags "-std=c++14")
set(
  CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${project_flags} ${clang_warn_flags}"
)

include_directories(src)

## Hack to make QtCreator show headers inside project window
file(GLOB_RECURSE header_files "src/*.hpp")
add_custom_target(headers SOURCES ${header_files})

add_subdirectory(src/lex)
add_subdirectory(src/dbg)
add_subdirectory(src/cc)
add_subdirectory(src/ast)
add_subdirectory(src/io)
add_subdirectory(src/sym)
add_subdirectory(src/dt)

## Main executable (mostly for debug purposes)
add_executable(${PROJECT_NAME} lisp.cpp)
target_link_libraries(${PROJECT_NAME} io cc ast lex sym dt dbg)
