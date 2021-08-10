cmake_minimum_required(VERSION 3.6)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build tests" ON)
option(BUILD_COVERAGE "Build coverage" OFF)

project(rw VERSION 1.1.0)

string(APPEND CMAKE_CXX_FLAGS " -pedantic -Wall -Wextra")
string(APPEND CMAKE_CXX_FLAGS " -Wno-unused-command-line-argument")
string(APPEND CMAKE_CXX_FLAGS " -Wshadow -Wnon-virtual-dtor")

find_package(Threads)

add_subdirectory(rw_lib)
add_subdirectory(prog)
