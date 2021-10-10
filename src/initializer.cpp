#include "initializer.h"

#include <sstream>
#include <GLFW/glfw3.h>
#include "error.h"

void glfwErrorHandle(int error, const char *description) {
    std::stringstream stringStream{};
    stringStream << "[Code: " << error << "]" << description;

    gl::errorHandle(gl::Error::GLFW, stringStream.str());
}

gl::Initializer::Initializer(gl::Version &version): version{version}, inited{false} {
}
gl::Initializer::Initializer(gl::Version &&version): version{version}, inited{false} {
}

gl::Initializer::~Initializer() {
    if (inited)
        glfwTerminate();
}

void gl::Initializer::init() {
    if (inited)
        return;

    if (!glfwInit()) {
        errorHandle(0, "Failed to initialize GLFW.");
        return;
    }

    glfwSetErrorCallback(glfwErrorHandle);

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, version.major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, version.minor);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

#ifndef NDEBUG
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif

    inited = true;
}