project(drizzle_client)

set(drizzle_src main.cc)
add_executable(drizzle_client ${drizzle_src})
target_link_libraries(drizzle_client drizzle)
