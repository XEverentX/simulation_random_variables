message(STATUS "algorithms")

file(GLOB HEADERS *.hpp)
file(GLOB SOURCES *.cpp)

add_library(algorithms ${SOURCES})

set_target_properties(algorithms PROPERTIES CXX_STANDARD 17)
