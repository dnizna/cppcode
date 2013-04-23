project(lex)
cmake_minimum_required(VERSION 2.6)

exec_program(lex ARGS "-osimple.c ../simple.l")
add_executable(simple "simple.c")
target_link_libraries(simple l)

exec_program(yacc ARGS "-d ../calc.y")
exec_program(lex ARGS "-ocalc.c ../calc.l")
add_executable(calc calc.c y.tab.c y.tab.h)
target_link_libraries(calc l)
#target_link_libraries(calc y)

exec_program(lex ARGS "-oword.c ../word.l")
add_executable(word "word.c")
target_link_libraries(word l)
