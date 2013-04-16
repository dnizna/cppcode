project(lex)
cmake_minimum_required(VERSION 2.6)

exec_program(lex ARGS "-osimple.c ../simple.l")
add_executable(simple "simple.c")
target_link_libraries(simple l)
