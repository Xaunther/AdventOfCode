include_directories("include" ${CMAKE_CURRENT_BINARY_DIR}/include)

file(GLOB SOURCES "src/*.cpp")

get_filename_component(DAY ${CMAKE_CURRENT_SOURCE_DIR} NAME)

string(CONCAT TARGET ${DAY} "_" ${YEAR})

configure_file( "include/day.h.in" "include/day.h" )

add_executable(${TARGET} ${SOURCES})