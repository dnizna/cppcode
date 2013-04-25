project(gmock)

set(gmock_src sample.cpp)
add_executable(sample ${gmock_src})
target_link_libraries(sample gtest pthread)
