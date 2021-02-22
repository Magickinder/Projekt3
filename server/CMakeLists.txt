cmake_minimum_required(VERSION 3.17)
project(server C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_compile_options(
        "-ggdb3"
        "-std=c11"
        "-xc"
        "-pedantic"
        "-Werror"
        "-Wall"
        "-Wextra"
        "-fmax-errors=5"
        "-Werror=vla"
        #"-Wno-error=unused-parameter"
        "-Wno-error=parentheses"
        "-Wno-parentheses"
        "-D_GNU_SOURCE"
        "-D__TEST_BOOTSTRAP"
        "-DINSIDE_DANTE"
        "-Wmultichar"
)

add_link_options(
        "-ggdb3"
        "-fuse-ld=gold"
        "-Wl,-Map=main.map"
        "-Wl,-cref"
)

add_executable(server
        functions.c
        functions.h
        main.c
)

target_link_libraries(server ncurses pthread rt)