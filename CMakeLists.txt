cmake_minimum_required(VERSION 3.0.0)
project(AdventOfCode VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories("./include/")

add_executable(day1 day1.cpp)
add_executable(day2 day2.cpp)
add_executable(day3 day3.cpp)

set_property(TARGET day1 PROPERTY CXX_STANDARD 20)
set_property(TARGET day2 PROPERTY CXX_STANDARD 20)
set_property(TARGET day3 PROPERTY CXX_STANDARD 20)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
