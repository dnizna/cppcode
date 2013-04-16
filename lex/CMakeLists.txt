project(lex)
cmake_minimum_required(VERSION 2.6)

exec_program(lex ARGS "../simple.l")
add_executable(first "lex.yy.c")
target_link_libraries(first l)
