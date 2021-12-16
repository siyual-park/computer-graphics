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

if (MINGW)
     set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -static-libgcc")
     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")
     set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "${CMAKE_SHARED_LIBRARY_LINK_C_FLAGS} -static-libgcc -s")
     set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "${CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS} -static-libgcc -static-libstdc++ -s")
endif()

add_subdirectory(external)
include_directories(
		include
		.
)

# Compile internal dependencies

set(
		APPLICATION_SOURCES
		src/error.cpp
		src/initializer.cpp
		src/window.cpp
		src/renderer.cpp
		src/gl-object.cpp
		src/program.cpp
		src/mouse.cpp
		src/camera.cpp
		src/scene.cpp
		src/mesh.cpp
		src/model.cpp
		src/world.cpp
		src/light.cpp
		src/material.cpp
		src/cube.cpp
        src/volume-surface.cpp
		src/frame-buffer.cpp
		src/texture2d.cpp
)

set(
		APPLICATION_HEADERS
		include/error.h
		include/initializer.h
		include/mouse.h
		include/window.h
		include/renderer.h
		include/gl-object.h
		include/shader.h
		include/shader-inc.h
		include/cast.h
		include/program.h
		include/program-inc.h
		include/drawable.h
		include/camera.h
		include/scene.h
		include/mesh.h
		include/model.h
		include/stb_image.h
		include/world.h
		include/light.h
		include/material.h
        include/event.h
		include/event-inc.h
		include/window-inc.h
		include/voxels.h
		include/voxels-inc.h
		include/voxels-reader.h
		include/voxels-reader-inc.h
		include/cube.h
        include/volume-surface.h
        include/volume.h
		include/frame-buffer.h
        include/texture2d.h
		include/volume-inc.h
		include/type.h
		include/texture2d-inc.h
)

add_library(
		APPLICATION_LIB STATIC
		${APPLICATION_HEADERS}
		${APPLICATION_SOURCES}
)

target_link_libraries(
		APPLICATION_LIB
		${OPENGL_LIBRARY}
		gl3w
		glfw
		glm
		assimp
)

set(
		ALL_LIBS
		APPLICATION_LIB
)

# assignment_1
add_executable(
		assignment_1
		assignment_1/main.cpp
		assignment_1/renderer.cpp
		assignment_1/scene.cpp
)
target_link_libraries(
		assignment_1
		${ALL_LIBS}
)

set_target_properties(assignment_1 PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/assignment_1/")

add_custom_command(
		TARGET assignment_1 POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_SOURCE_DIR}/assignment_1/shaders $<TARGET_FILE_DIR:assignment_1>/shaders
		COMMENT "Copying shaders" VERBATIM
)
add_custom_command(
		TARGET assignment_1 POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_SOURCE_DIR}/shaders $<TARGET_FILE_DIR:assignment_1>/shaders
		COMMENT "Copying shaders" VERBATIM
)

add_custom_command(
		TARGET assignment_1 POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_SOURCE_DIR}/assignment_1/resources $<TARGET_FILE_DIR:assignment_1>/resources
		COMMENT "Copying resources" VERBATIM
)

# assignment_2
add_executable(
		assignment_2
		assignment_2/main.cpp
		assignment_2/renderer.cpp
		assignment_2/scene.cpp
)
target_link_libraries(
		assignment_2
		${ALL_LIBS}
)

set_target_properties(assignment_2 PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/assignment_2/")

add_custom_command(
		TARGET assignment_2 POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_SOURCE_DIR}/assignment_2/shaders $<TARGET_FILE_DIR:assignment_2>/shaders
		COMMENT "Copying shaders" VERBATIM
)
add_custom_command(
		TARGET assignment_2 POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_SOURCE_DIR}/shaders $<TARGET_FILE_DIR:assignment_2>/shaders
		COMMENT "Copying shaders" VERBATIM
)

add_custom_command(
		TARGET assignment_2 POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_SOURCE_DIR}/assignment_2/resources $<TARGET_FILE_DIR:assignment_2>/resources
		COMMENT "Copying resources" VERBATIM
)