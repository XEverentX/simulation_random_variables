message(STATUS "samples")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5Widgets)
find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5PrintSupport)

add_executable(simulate
               mainwindow.cpp
               mainwindow.ui
               main.cpp
               qcustomplot.cpp
)

target_link_libraries(simulate simulation)
target_link_libraries(simulate Qt5::Widgets Qt5::PrintSupport)

set_target_properties(simulate PROPERTIES CXX_STANDARD 17)