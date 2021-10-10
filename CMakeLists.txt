# CMake entry point
cmake_minimum_required (VERSION 3.0)
project (OpenGLBoilerplate)

find_package(OpenGL REQUIRED)

# Compile external dependencies

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(external)
include_directories(
		external/glfw-3.3.4/include
		include
		.
)

set(
		APPLICATION_SOURCES
		src/main.cpp
)

set(
		APPLICATION_HEADERS
		include/application.h
)

add_library(
		APPLICATION_FILES STATIC
		${APPLICATION_SOURCES}
		${APPLICATION_HEADERS}
)

target_link_libraries(
		APPLICATION_FILES
		${OPENGL_LIBRARY}
		glfw
)

set(
		ALL_LIBS
		${OPENGL_LIBRARY}
		glfw
)


# chapter 1
add_executable(
		application
		src/main.cpp
)
target_link_libraries(
		application
		${ALL_LIBS}
)
