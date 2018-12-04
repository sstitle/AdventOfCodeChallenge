cmake_minimum_required(VERSION 2.8.3)
project(AdventCalendarDay2)

set(CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "-ggdb")

set(SRC
  main.cpp
)

add_executable(day_2 ${SRC})
