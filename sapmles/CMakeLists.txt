message(STATUS "samples")

add_executable(simulation simulation.cpp)

target_link_libraries(simulation algorithms)
set_target_properties(simulation PROPERTIES CXX_STANDARD 17)
