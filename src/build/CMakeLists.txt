cmake_minimum_required(VERSION 3.5)

project(calc LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17 -Wall -Werror -Wextra -g -fsanitize=address -static-libasan")
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17 -Wall -Werror -Wextra")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

add_executable(calc
  ../view/main.cpp
  ../view/widget.cpp
  ../view/widget.h
  ../view/slots.cpp
  ../view/draw.cpp
  ../view/events.cpp
  ../view/graphicsview.h
  ../view/textedit.h
  ../view/widget.ui
  ../controller/controller.cpp
  ../controller/controller.h
  ../model/element.cpp
  ../model/model.h
  ../model/element.h
  ../model/modelCalc.cpp
  ../model/graph.cpp
  ../model/moves.cpp
  ../model/find_graph.cpp
)

target_include_directories(calc PUBLIC ../view)


if(QT_VERSION_MAJOR EQUAL 6)
  target_link_libraries(calc PRIVATE Qt6::Widgets)
else()
  target_link_libraries(calc PRIVATE Qt5::Widgets)
endif()
