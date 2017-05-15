cmake_minimum_required(VERSION 3.7)
project(fish_shell)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-Wall -Werror -pedantic -fpic -Wextra -Wshadow")

file(GLOB SOURCE_FILES *)
add_executable(fish ${SOURCE_FILES})