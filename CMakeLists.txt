# CMake entry point
cmake_minimum_required (VERSION 3.0)
project (OpenGLBoilerplate)

find_package(OpenGL REQUIRED)

set (CMAKE_CXX_STANDARD 20)
# Fix behavior of CMAKE_CXX_STANDARD when targeting macOS.
if (POLICY CMP0025)
	cmake_policy(SET CMP0025 NEW)
endif ()

if (MINGW)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lole32 -loleaut32 -static-libgcc -static")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lole32 -loleaut32 -static-libgcc -static-libstdc++ -static")
	set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "${CMAKE_SHARED_LIBRARY_LINK_C_FLAGS} -lole32 -loleaut32 -static-libgcc -s -static")
	set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "${CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS} -lole32 -loleaut32 -static-libgcc -static-libstdc++ -s -static")
endif()

# Compile external dependencies

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

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
        src/read-voxels.cpp
		src/transfer-function.cpp
        src/endian-type.cpp
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
		include/world.h
		include/light.h
		include/material.h
        include/event.h
		include/event-inc.h
		include/window-inc.h
		include/voxels.h
		include/voxels-inc.h
        include/read-voxels.h
		include/read-voxels-inc.h
		include/cube.h
        include/volume-surface.h
        include/volume.h
		include/volume-inc.h
		include/frame-buffer.h
		include/type.h
		include/texture1d.h
		include/texture1d-inc.h
		include/texture2d.h
		include/texture2d-inc.h
		include/texture3d.h
		include/texture3d-inc.h
		include/endian-type.h
		include/transfer-function-gen.h
		include/transfer-function-gen-inc.h
        include/read-raw.h
		include/read-raw-inc.h
		include/transfer-function.h
		include/stb_image.h
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
)
target_link_libraries(
		assignment_2
		${ALL_LIBS}
)

set_target_properties(assignment_2 PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/assignment_2/")

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

# assignment_2_transfer_function_gen
add_executable(
		assignment_2_transfer_function_gen
		assignment_2_transfer_function_gen/main.cpp
)
target_link_libraries(
		assignment_2_transfer_function_gen
		${ALL_LIBS}
)

set_target_properties(assignment_2_transfer_function_gen PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/assignment_2/")

add_custom_command(
		TARGET assignment_2_transfer_function_gen POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_SOURCE_DIR}/shaders $<TARGET_FILE_DIR:assignment_2>/shaders
		COMMENT "Copying shaders" VERBATIM
)
