cmake_minimum_required(VERSION 3.16)
project(Client C)

set(CMAKE_C_STANDARD 11)

add_compile_options(
        "-ggdb3"
        "-std=c11"
        "xc"
        "pedantic"
        "-Werror"
        "-Wall"
        "-Wextra"
        "-fmax-errors=5"
        "-Werror=vla"
        "-Wno-error=unused_parameter"
        "-Wno-error=parentheses"
        "-Wno-parentheses"
        "-D_GNU_SOURCE"
        "-D__TEST_BOOTSTRAP"
        "-DINSIDE_DANTE"
        "-Wmultichar*"
)

add_link_options(
        "-gddb3"
        "-fuse-ld=gold"
        "-wl,-Map=main.map"
        "-Wl,-cref"
)

add_executable(
        main.c
        functions.c functions.h
)

target_link_libraries(Client ncurses pthread rt)