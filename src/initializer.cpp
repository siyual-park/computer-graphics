#include "initializer.h"

#include <sstream>
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include "error.h"

void glfwErrorHandle(int error, const char *description) {
    std::stringstream stringStream{};
    stringStream << "[Code: " << error << "]" << description;

    gl::errorHandle(gl::Error::GLFW, stringStream.str());
}

gl::Initializer::Initializer(gl::Version &version): version{version}, inited{false}, loaded{false} {
}
gl::Initializer::Initializer(gl::Version &&version): version{version}, inited{false}, loaded{false} {
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

void gl::Initializer::load() {
    if (loaded)
        return;

    if (gl3wInit()) {
        errorHandle(Error::GL3W, "Failed to initialize gl3w.");
        return;
    }
    if (!gl3wIsSupported(version.major, version.minor)) {
        errorHandle(Error::GL3W, "This version not supported.");
        return;
    }

    loaded = true;
}