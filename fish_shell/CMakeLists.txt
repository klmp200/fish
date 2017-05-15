cmake_minimum_required(VERSION 3.7)
project(fish_shell)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-Wall -Werror -pedantic -fpic -Wextra -Wshadow")

set(SOURCE_FILES main.c fish_core.c fish_core.h fish_commands.c fish_commands.h fish_types.h fish_utils.c fish_utils.h fish_globbing.c fish_globbing.h)
add_executable(fish ${SOURCE_FILES})
