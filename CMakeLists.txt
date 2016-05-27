SET(CMAKE_C_COMPILER "/usr/bin/clang")
SET(CMAKE_CXX_COMPILER "/usr/bin/clang++")

project(Resembler)
cmake_minimum_required(VERSION 2.8)

## Project-wide settings
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
set(project_flags "-std=c++1z")
set(
  CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${project_flags} ${clang_warn_flags}"
)

include_directories("src" "tests")

## Hack to make QtCreator show headers inside project window
file(GLOB_RECURSE header_files "src/*.hpp" "tests/*.hpp" "src/backend/cpp/rt/*.h")
add_custom_target(headers SOURCES ${header_files})

add_subdirectory(src/lex)
add_subdirectory(src/dbg)
add_subdirectory(src/cc)
add_subdirectory(src/ast)
add_subdirectory(src/io)
add_subdirectory(src/sym)
add_subdirectory(src/intrinsic)
add_subdirectory(src/dt)
add_subdirectory(src/fmt)
add_subdirectory(src/backend/cpp/cg)
add_subdirectory(src/di)
add_subdirectory(src/util)
add_subdirectory(src/unit)
add_subdirectory(src/app)

## Tests
enable_testing()
add_subdirectory(tests/test_dt)
add_subdirectory(tests/test_cc)
# add_subdirectory(tests/test_sym)

## Main executable (mostly for debug purposes)
add_executable(${PROJECT_NAME} lisp.cpp)
target_link_libraries(
  ${PROJECT_NAME} cpp_cg cc ast lex unit fmt dbg sym intrinsic app di io dt
)

add_executable(rt rt.cpp)
target_link_libraries(rt)
