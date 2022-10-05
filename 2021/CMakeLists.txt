include_directories("include" ${CMAKE_CURRENT_BINARY_DIR}/include)

get_filename_component(YEAR ${CMAKE_CURRENT_SOURCE_DIR} NAME)

configure_file( "include/year.h.in" "include/year.h" )

add_subdirectory(day1)
add_subdirectory(day2)
add_subdirectory(day3)
add_subdirectory(day4)
add_subdirectory(day5)
add_subdirectory(day6)
add_subdirectory(day7)
add_subdirectory(day8)
add_subdirectory(day9)
add_subdirectory(day10)