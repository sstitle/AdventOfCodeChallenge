cmake_minimum_required(VERSION 2.8.3)
project(AdventCalendarDay3)

set(CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "-ggdb")

find_package(OpenCV REQUIRED)

set(SRC
  main.cpp
)

add_executable(AdventCalendarDay3 ${SRC})
target_link_libraries(AdventCalendarDay3 ${OpenCV_LIBS})
