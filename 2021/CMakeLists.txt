include_directories("include" ${CMAKE_CURRENT_BINARY_DIR}/include)

get_filename_component(YEAR ${CMAKE_CURRENT_SOURCE_DIR} NAME)

configure_file( "include/year.h.in" "include/year.h" )

add_subdirectory(day1)
add_subdirectory(day2)
add_subdirectory(day3)