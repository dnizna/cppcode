project(testpthread)

set(CMAKE_CXX_FLAGS "-g")
set(testpthread_src main.cc test.h basic.cc threadlocal.cc threadlock.cc pthreadcond.cc)
add_executable(testpthread ${testpthread_src})
target_link_libraries(testpthread pthread)
