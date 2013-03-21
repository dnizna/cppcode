project(easy)
cmake_minimum_required(VERSION 2.6)

set(easy_src main.cc)
add_executable(testeasy ${easy_src})
include_directories(/usr/local/include/easy)
target_link_libraries(testeasy easy pthread)
