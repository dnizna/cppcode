project(testpthread)

set(testpthread_src main.cc test.h basic.cc threadlocal.cc)
add_executable(testpthread ${testpthread_src})
target_link_libraries(testpthread pthread)
