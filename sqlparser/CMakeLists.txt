project(sqlparser)
cmake_minimum_required(VERSION 2.6)

set(CMAKE_CXX_FLAG "-g")
exec_program(bison ARGS "-d ../sql_parser.y")
exec_program(lex ARGS "-osql_parser.c ../sql_parser.l")
exec_program(cp ARGS "*.c *.h ..")
add_executable(sqlparser sql_node.h sql_parser.c sql_parser.lex.h create_table.h sql_parser.tab.c sql_parser.tab.h main.cpp)
target_link_libraries(sqlparser l)
