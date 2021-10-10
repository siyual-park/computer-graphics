# CMake entry point
cmake_minimum_required (VERSION 3.0)
project (OpenGLBoilerplate)

find_package(OpenGL REQUIRED)

set (CMAKE_CXX_STANDARD 11)
# Fix behavior of CMAKE_CXX_STANDARD when targeting macOS.
if (POLICY CMP0025)
	cmake_policy(SET CMP0025 NEW)
endif ()

# Compile external dependencies

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(external)
include_directories(
		external/glfw-3.3.4/include
		include
		.)

set(
		APPLICATION_SOURCES
		src/callback.cpp
		src/window.cpp
		src/initializer.cpp
		src/error.cpp
		)

set(
		APPLICATION_HEADERS
		include/callback.h
		include/mouse.h
		include/window.h
		include/initializer.h
		include/error.h
		)

add_library(
		APPLICATION_LIB STATIC
		${APPLICATION_HEADERS}
		${APPLICATION_SOURCES})

target_link_libraries(
		APPLICATION_LIB
		${OPENGL_LIBRARY}
		glfw)

set(
		ALL_LIBS
		APPLICATION_LIB
		)


add_executable(
		application
		src/main.cpp)
target_link_libraries(
		application
		${ALL_LIBS})
