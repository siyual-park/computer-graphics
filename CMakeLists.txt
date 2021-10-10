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
		include
		.)

# Compile internal dependencies

set(
		APPLICATION_SOURCES
		src/error.cpp
		src/initializer.cpp
		src/window.cpp
		src/renderer.cpp
		src/base-object.cpp
		src/program.cpp
		src/mouse.cpp
		src/camera.cpp src/scene.cpp)

set(
		APPLICATION_HEADERS
		include/callback.h
		include/callback-inc.h
		include/control.h
		include/control-inc.h
		include/error.h
		include/initializer.h
		include/mouse.h
		include/window.h
		include/renderer.h
		include/base-object.h
		include/shader.h
		include/shader-inc.h
		include/cast.h
		include/program.h
		include/program-inc.h
		include/drawable.h
		include/camera.h include/scene.h)

add_library(
		APPLICATION_LIB STATIC
		${APPLICATION_HEADERS}
		${APPLICATION_SOURCES})

target_link_libraries(
		APPLICATION_LIB
		${OPENGL_LIBRARY}
		gl3w
		glfw
		glm
		)

set(
		ALL_LIBS
		APPLICATION_LIB
		)

add_executable(
		assignment_1
		assignment_1/main.cpp
		assignment_1/callback.cpp
		assignment_1/renderer.cpp
		assignment_1/scene.cpp)
target_link_libraries(
		assignment_1
		${ALL_LIBS})

set_target_properties(assignment_1 PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/assignment_1/")

add_custom_command(
		TARGET assignment_1 POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_SOURCE_DIR}/assignment_1/shaders $<TARGET_FILE_DIR:assignment_1>/shaders
		COMMENT "Copying shaders" VERBATIM
)
