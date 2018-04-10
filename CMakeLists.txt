cmake_minimum_required(VERSION 3.10)
project(cube)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenGL REQUIRED)
find_package(GLFW3 REQUIRED)
find_package(GLM REQUIRED)
find_package(glew REQUIRED)


set(ALL_LIBS ${OPENGL_LIBRARY} glfw GLEW)

include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLEW_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} )
add_executable(cube main.cpp cube.cpp cube.h drawer.cpp drawer.h glcommon.h shader.cpp shader.h)

target_link_libraries(cube ${ALL_LIBS})