#ifndef OPENGLBOILERPLATE_ERROR_H
#define OPENGLBOILERPLATE_ERROR_H

#include <string>

#define GL_ERROR() gl::checkForOpenGLError(__FILE__, __LINE__)

namespace gl {
    enum Error {
        GLFW,
        GL3W,
        GL,
    };

    void checkForOpenGLError(const char* file, int line);
    void errorHandle(int error, const std::string &description);
}

#endif //OPENGLBOILERPLATE_ERROR_H
