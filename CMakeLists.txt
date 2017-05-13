cmake_minimum_required(VERSION 3.7)
project(fish)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-Wall -Werror -pedantic -fpic -Wextra")

set(SOURCE_FILES main.c fish_lib/fish_lib.c fish_lib/fish_lib.h)
add_executable(fish ${SOURCE_FILES})