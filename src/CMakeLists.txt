project(glengine CXX)
cmake_minimum_required(VERSION 2.8.7)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(log4cpp REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

set(CONF_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}" "${OPENGL_INCLUDE_DIR}" "${GLEW_INCLUDE_DIRS}" "${LOG4CPP_INCLUDE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}")
include_directories(.)
aux_source_directory(glengine SRC_LIST)

add_library(${PROJECT_NAME} SHARED ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${LOG4CPP_LIBRARIES} ${GLEW_LIBRARIES})

configure_file(${PROJECT_NAME}Config.cmake.in
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake" @ONLY)
export(TARGETS ${PROJECT_NAME}
  FILE "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Targets.cmake")
export(PACKAGE ${PROJECT_NAME})

