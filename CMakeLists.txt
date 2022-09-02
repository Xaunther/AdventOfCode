cmake_minimum_required(VERSION 3.15.1)
project(AdventOfCode)

set (CMAKE_CXX_STANDARD 20)
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	set (CMAKE_CXX_FLAGS "-O2 -W4 -WX -EHsc" )
else()
	set (CMAKE_CXX_FLAGS "-O2 -Wall -Werror -Wextra -Wpedantic" )
endif()

add_subdirectory(2020)
