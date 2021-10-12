#include "error.h"

#include <stdexcept>
#include <string>

namespace gl {
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
