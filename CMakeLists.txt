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
  src/GameOfLife/Parameters.cpp
  src/GameOfLife/Graphics/Renderer.cpp)

if (WIN32)
  include_directories(${CMAKE_SOURCE_DIR}/SFML-2.5.1_win32/include)
  link_directories(${CMAKE_SOURCE_DIR}/SFML-2.5.1_win32/lib)
  add_custom_target(deploy ALL)
  add_custom_command(TARGET deploy POST_BUILD
		     COMMAND ${CMAKE_COMMAND} -E copy_directory
			"${CMAKE_SOURCE_DIR}/SFML-2.5.1_win32/bin"
			${CMAKE_BINARY_DIR}/Release)
else()
  find_package(SFML 2.5 COMPONENTS graphics REQUIRED)
endif()

add_executable(agof ${SOURCES})
target_link_libraries(agof sfml-graphics sfml-window sfml-system)
