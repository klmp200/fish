cmake_minimum_required(VERSION 3.7)
project(fish_shell_tests)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

include_directories(
        "${source_dir}/googletest/include"
        "${source_dir}/googlemock/include"
)

set(SOURCE_FILES_TESTS main.cpp FishCoreTests.cpp FishUtilsTests.cpp)

add_executable(fish_tests ${SOURCE_FILES_TESTS})

target_link_libraries(fish_tests libgtest libgmock)

