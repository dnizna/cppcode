project(hello)

# macro test
set(macro_src macro.c)
add_executable(macro ${macro_src})

set(endian_src endian.cc)
add_executable(endian ${endian_src})

set(cast_src cast.cc)
add_executable(cast ${cast_src})

set(align_src align.cc)
add_executable(align ${align_src})
