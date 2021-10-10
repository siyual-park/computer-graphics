#include "error.h"

#include <string>

namespace gl {
    void errorHandle(int error, const std::string &description) {
        std::string errorDescription{"Error["};
        switch (error) {
            case Error::GL:errorDescription.append("GL");
                break;
            case Error::GLFW:errorDescription.append("GLFW");
                break;
            default:errorDescription.append("Undefined");
                break;
        }
        errorDescription.append("]: ");
        errorDescription.append(description);

        throw std::runtime_error{errorDescription};
    }
}
