project(opengl_examples)
cmake_minimum_required(VERSION 2.8.7)
option(BUILD_EXAMPLES "Build examples" OFF)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
SET(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/;${CMAKE_MODULE_PATH}")
add_definitions(-std=c++11)

include(ExternalProject)
ExternalProject_Add (
	glm
	PREFIX ${CMAKE_BINARY_DIR}/glm
	GIT_REPOSITORY https://github.com/g-truc/glm.git
	INSTALL_COMMAND ""
	BUILD_COMMAND ""
	LOG_DOWNLOAD ON
	)
ExternalProject_Get_Property(glm source_dir)
set(GLM_INCLUDE_DIRS ${source_dir})
include_directories(${GLM_INCLUDE_DIRS})

add_subdirectory(src)
if(BUILD_EXAMPLES)
	add_subdirectory(examples)
endif(BUILD_EXAMPLES)
