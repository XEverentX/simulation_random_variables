message(STATUS "simulation")

file(GLOB HEADERS *.hpp)
file(GLOB SOURCES *.cpp)

add_library(simulation ${HEADERS} ${SOURCES})
target_include_directories(simulation PUBLIC ./)

set_target_properties(simulation PROPERTIES CXX_STANDARD 17)
