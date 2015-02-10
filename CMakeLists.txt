project(opengl_examples)
cmake_minimum_required(VERSION 2.8.7)
# CMAKE BUILD OPTIONS
option(BUILD_EXAMPLES "Build examples" OFF)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

option(DOWNLOAD_THIRD_PARTY_LIBS OFF)

# Instruct CMake to run moc automatically when needed.
SET(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/;${CMAKE_MODULE_PATH}")
add_definitions(-std=c++11)

if(DOWNLOAD_THIRD_PARTY_LIBS)

include(ExternalProject)
ExternalProject_Add (
	glm
	URL "http://github.com/g-truc/glm/archive/0.9.6.1.tar.gz"
	INSTALL_COMMAND ""
	LOG_DOWNLOAD ON
	LOG_BUILD ON
	LOG_CONFIGURE ON
	)
ExternalProject_Get_Property(glm source_dir)

set(GLM_INCLUDE_DIRS ${source_dir})
include_directories(${GLM_INCLUDE_DIRS})

ExternalProject_Add(
	GLFW
	URL "https://github.com/glfw/glfw/archive/3.1.tar.gz"
	INSTALL_COMMAND ""
	LOG_DOWNLOAD ON
	LOG_BUILD ON
	LOG_CONFIGURE ON
	)

ExternalProject_Get_Property(GLFW source_dir)
set(GLFW_INCLUDE_DIRS ${source_dir}/include) 
ExternalProject_Get_Property(GLFW binary_dir)
set(GLFW_LIBRARY_PATH ${binary_dir}/src/${CMAKE_FIND_LIBRARY_PREFIXES}glfw3.a)
set(GLFW_LIBRARY glfw)
add_library(${GLFW_LIBRARY} UNKNOWN IMPORTED) 
set_property(TARGET ${GLFW_LIBRARY} PROPERTY IMPORTED_LOCATION
	${GLFW_LIBRARY_PATH} )
add_dependencies(${GLFW_LIBRARY} GLFW) 
set(GLFW_LIBRARIES ${GLFW_LIBRARY})
endif(DOWNLOAD_THIRD_PARTY_LIBS)

add_subdirectory(src)
if(BUILD_EXAMPLES)
	add_subdirectory(examples)
endif(BUILD_EXAMPLES)
