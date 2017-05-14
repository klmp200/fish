cmake_minimum_required(VERSION 3.7)
project(fish)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-Wall -Werror -pedantic -fpic -Wextra")

set(SOURCE_FILES main.c fish_shell/fish_core.c fish_shell/fish_core.h fish_shell/fish_commands.c fish_shell/fish_commands.h fish_shell/fish_types.h)
add_executable(fish ${SOURCE_FILES})