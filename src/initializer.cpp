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

#ifndef NDEBUG
void glErrorHandle(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                   const GLchar *message, const void *userParam) {
    // Print, log, whatever based on the enums and message
    gl::errorHandle(gl::Error::GL, message);
}
#endif

gl::Version gl::version{};
bool gl::inited_window_system = false;
bool gl::inited_gl_loader = false;

void gl::setVersion(Version new_version) {
    gl::version = new_version;
}

void gl::initWindowSystem() {
    if (inited_window_system)
        return;

    if (!glfwInit()) {
        errorHandle(0, "Failed to initialize GLFW.");
        return;
    }

    glfwSetErrorCallback(glfwErrorHandle);

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, gl::version.major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, gl::version.minor);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    inited_window_system = true;
}
void gl::initGLLoader() {
    if (inited_gl_loader)
        return;

    if (gl3wInit()) {
        errorHandle(Error::GL3W, "Failed to initialize gl3w.");
        return;
    }
    if (!gl3wIsSupported(version.major, version.minor)) {
        errorHandle(Error::GL3W, "This version not supported.");
        return;
    }

    GL_ERROR();

#ifndef NDEBUG
    GLint flags;
    glGetIntegerv(GL_CONTEXT_FLAGS, &flags);

    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(glErrorHandle, nullptr);

        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    }
#endif

    inited_gl_loader = true;
}
