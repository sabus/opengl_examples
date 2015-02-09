project(opengl_examples)
cmake_minimum_required(VERSION 2.8.7)
option(BUILD_EXAMPLES "Build examples" OFF)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
SET(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/;${CMAKE_MODULE_PATH}")
add_definitions(-std=c++11)

add_subdirectory(src)
if(BUILD_EXAMPLES)
	add_subdirectory(examples)
endif(BUILD_EXAMPLES)
