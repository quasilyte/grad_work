project(lexer_test)

set(quick_test_src quick_test.cpp)

add_executable(quick_test ${quick_test_src})
target_link_libraries(quick_test lex)

add_test(quick_test quick_test)
