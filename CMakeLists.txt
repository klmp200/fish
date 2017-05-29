cmake_minimum_required(VERSION 3.5)
project(fish_shell)

# We need thread support
find_package(Threads REQUIRED)

# Enable ExternalProject CMake module
include(ExternalProject)

# Download and install GoogleTest
ExternalProject_Add(
        gtest
        URL https://github.com/google/googletest/archive/master.zip
        PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
        # Disable install step
        INSTALL_COMMAND ""
)

# Get GTest source and binary directories from CMake project
ExternalProject_Get_Property(gtest source_dir binary_dir)

# Create a libgtest target to be used as a dependency by test programs
add_library(libgtest IMPORTED STATIC GLOBAL)
add_dependencies(libgtest gtest)

# Set libgtest properties
set_target_properties(libgtest PROPERTIES
        "IMPORTED_LOCATION" "${binary_dir}/googlemock/gtest/libgtest.a"
        "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
        )

# Create a libgmock target to be used as a dependency by test programs
add_library(libgmock IMPORTED STATIC GLOBAL)
add_dependencies(libgmock gtest)

# Set libgmock properties
set_target_properties(libgmock PROPERTIES
        "IMPORTED_LOCATION" "${binary_dir}/googlemock/libgmock.a"
        "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
        )

include_directories(
        "${source_dir}/googletest/include"
        "${source_dir}/googlemock/include"
)


set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-Wall -Werror -pedantic -fpic -Wextra -Wshadow")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FALGS} -g")
set(CMAKE_EXE_LINKER_FLAGS "-lpcre")

set(SOURCE_FILES fish_shell/main.c fish_shell/fish_types.h fish_shell/fish_core.h fish_shell/fish_core.c fish_shell/fish_commands.c fish_shell/fish_commands.h fish_shell/fish_globbing.c fish_shell/fish_globbing.h fish_shell/fish_utils.c fish_shell/fish_utils.h fish_settings.c fish_settings.h)
add_executable(fish ${SOURCE_FILES})

#add_subdirectory(fish_shell)

add_subdirectory(fish_shell_tests)

enable_testing()

add_test(NAME fish_tests
        COMMAND fish_tests
)
