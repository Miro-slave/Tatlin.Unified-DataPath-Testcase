cmake_minimum_required(VERSION 3.28.3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(tape)

add_subdirectory(src)
add_subdirectory(bin)

add_subdirectory(tests)
