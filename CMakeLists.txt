cmake_minimum_required(VERSION 3.16)

project(latexDSL)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(lexer_tests
tests/lexer_tests.cpp
)

add_executable(parser_tests
tests/parser_tests.cpp
src/utils/ast_utils.cpp
)

add_executable(renderer_tests
tests/renderer_tests.cpp
)

add_executable(repl
tools/repl/main.cpp
)

