cmake_minimum_required(VERSION 3.15.1)
project(AdventOfCode)

set (CMAKE_CXX_STANDARD 20)
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	set (CMAKE_CXX_FLAGS "-O2 -W4 -EHsc" )
else()
	set (CMAKE_CXX_FLAGS "-O2 -Wall -Wextra -Wpedantic" )
endif()

add_subdirectory(2020)
add_subdirectory(2021)
add_subdirectory(2022)
