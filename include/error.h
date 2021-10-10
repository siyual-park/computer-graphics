#ifndef OPENGLBOILERPLATE_ERROR_H
#define OPENGLBOILERPLATE_ERROR_H

#include <string>

namespace gl {
    enum Error {
        GLFW,
        GL,
    };

    void errorHandle(int error, const std::string &description);
}

#endif //OPENGLBOILERPLATE_ERROR_H
