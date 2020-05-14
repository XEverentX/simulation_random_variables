cmake_minimum_required(VERSION 3.12)

project(simulation_random_variable)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5Widgets)
find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5PrintSupport)

file(GLOB HEADERS /*.hpp)
file(GLOB SOURCES simulation/*.cpp)

add_library(simulation ${HEADERS} ${SOURCES})
target_include_directories(simulation PUBLIC ./simulation/)

set_target_properties(simulation PROPERTIES CXX_STANDARD 17)

add_executable(simulate
               application/mainwindow.cpp
               application/main.cpp
               application/qcustomplot.cpp
)

target_link_libraries(simulate simulation)
target_link_libraries(simulate Qt5::Widgets Qt5::PrintSupport)

set_target_properties(simulate PROPERTIES CXX_STANDARD 17)
