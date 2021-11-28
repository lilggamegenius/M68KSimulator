cmake_minimum_required(VERSION 3.16)
project(M68KSimulator)

set(CMAKE_CXX_STANDARD 20)

add_compile_options(-Wall -Wextra -Wno-unknown-pragmas -Werror)
add_compile_options(
        "-Wall" "-Werror" "-Wextra"
        "$<$<CONFIG:DEBUG>:-O0;-g3;-ggdb;-Wno-unknown-pragmas;>"
)
add_subdirectory(Simulator)
add_subdirectory(Tests)