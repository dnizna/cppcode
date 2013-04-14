project(ev)

set(CMAKE_CXX_FLAGS "-g")
set(ev_src ev.h ev.c main.cc)
add_executable(ev ${ev_src})

set(evio_server_src ev.h ev.c evio.cc conn_queue.h conn_queue.cc dispatch_thread.h dispatch_thread.cc work_thread.h work_thread.cc)
add_executable(evio_server ${evio_server_src})
target_link_libraries(evio_server pthread)

set(evio_client_src client.cc)
add_executable(evio_client ${evio_client_src})
target_link_libraries(evio_client pthread)
