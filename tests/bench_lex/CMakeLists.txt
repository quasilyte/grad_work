project(lex_bench)

set(
  lex_bench_src
  m9_read.cpp
)

add_executable(lex_bench ${lex_bench_src})
target_link_libraries(lex_bench lex chars dt rodata)

add_test(lex_bench lex_bench)
