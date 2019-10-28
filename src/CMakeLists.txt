cmake_minimum_required(VERSION 3.1)

if (CMAKE_COMPILER_IS_GNUCC)
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
elseif (MSVC)
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
endif()

project(agof)
set(agof_VERSION_MAJOR 1)
set(agof_VERSION_MINOR 0)

include_directories(${CMAKE_SOURCE_DIR}/inc)

set (SOURCES
  src/main.cpp
  src/GameOfLife/Board.cpp
  src/GameOfLife/Parameters.cpp)

add_executable(agof ${SOURCES})
