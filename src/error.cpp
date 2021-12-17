#include "error.h"

#include <GL/gl3w.h>
#include <stdexcept>
#include <string>

namespace gl {
    void checkForOpenGLError(const char* file, int line) {
        GLenum errorCode;
        while ((errorCode = glGetError()) != GL_NO_ERROR) {
            std::string error;
            switch (errorCode) {
                case GL_INVALID_ENUM:
                    error = "INVALID_ENUM";
                    break;
                case GL_INVALID_VALUE:
                    error = "INVALID_VALUE";
                    break;
                case GL_INVALID_OPERATION:
                    error = "INVALID_OPERATION";
                    break;
                case GL_STACK_OVERFLOW:
                    error = "STACK_OVERFLOW";
                    break;
                case GL_STACK_UNDERFLOW:
                    error = "STACK_UNDERFLOW";
                    break;
                case GL_OUT_OF_MEMORY:
                    error = "OUT_OF_MEMORY";
                    break;
                case GL_INVALID_FRAMEBUFFER_OPERATION:
                    error = "INVALID_FRAMEBUFFER_OPERATION";
                    break;
            }

            std::string error_description{"Error[GL]: "};

            error_description.append(error);
            error_description.append(", file: ");
            error_description.append(file);
            error_description.append(", line: ");
            error_description.append(std::to_string(line));

            throw std::runtime_error{error_description};
        }
    }

    void errorHandle(int error, const std::string &description) {
        std::string error_description{"Error["};
        switch (error) {
            case Error::GL:
                error_description.append("GL");
                break;
            case Error::GLFW:
                error_description.append("GLFW");
                break;
            default:
                error_description.append("Undefined");
                break;
        }
        error_description.append("]: ");
        error_description.append(description);

        throw std::runtime_error{error_description};
    }
}
