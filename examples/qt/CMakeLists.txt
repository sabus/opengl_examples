project(opengl_with_qt)
cmake_minimum_required(VERSION 2.8.7)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.

find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)
find_package(glengine REQUIRED) #defines GLENGINE_INCLUDE_DIRS GLENGINE_LIBRARIES
set(CMAKE_AUTOMOC ON)
configure_file(logger.properties logger.properties COPYONLY)
set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
include_directories(${GLENGINE_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS} ${Qt5OpenGL_INCLUDE_DIRS})
aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} ${QT_LIBRARIES} ${GLENGINE_LIBRARIES} ${Qt5Widgets_LIBRARIES} ${Qt5OpenGL_LIBRARIES})

