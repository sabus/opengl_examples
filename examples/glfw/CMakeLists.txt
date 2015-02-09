project(opengl_with_glfw)
cmake_minimum_required(VERSION 2.8.7)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
find_package(glengine REQUIRED) #defines GLENGINE_INCLUDE_DIRS GLENGINE_LIBRARIES
configure_file(logger.properties logger.properties COPYONLY)
include_directories(${GLENGINE_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS} src)
aux_source_directory(src SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} ${GLFW_LIBRARIES} ${GLENGINE_LIBRARIES})

