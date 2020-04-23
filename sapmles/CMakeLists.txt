message(STATUS "samples")

add_executable(simulate simulation.cpp)

target_link_libraries(simulate simulation)
set_target_properties(simulate PROPERTIES CXX_STANDARD 17)
