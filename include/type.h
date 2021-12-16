#ifndef OPENGLBOILERPLATE_TYPE_H
#define OPENGLBOILERPLATE_TYPE_H

#include <GL/gl3w.h>

namespace gl {
    template <typename T>
    constexpr int getType() {
        return 0;
    }

    template <float*>
    constexpr int getType() {
        return GL_FLOAT;
    }

    template <signed char*>
    constexpr int getType() {
        return GL_BYTE;
    }

    template <unsigned char*>
    constexpr int getType() {
        return GL_UNSIGNED_BYTE;
    }

    template <signed short*>
    constexpr int getType() {
        return GL_SHORT;
    }

    template <unsigned short*>
    constexpr int getType() {
        return GL_UNSIGNED_SHORT;
    }

    template <int*>
    constexpr int getType() {
        return GL_INT;
    }

    template <unsigned int*>
    constexpr int getType() {
        return GL_UNSIGNED_INT;
    }

    template <typename T>
    constexpr int getRedType() {
        return 0;
    }

    template <float*>
    constexpr int getRedType() {
        return GL_R16F;
    }

    template <signed char*>
    constexpr int getRedType() {
        return GL_R8_SNORM;
    }

    template <unsigned char*>
    constexpr int getRedType() {
        return GL_R8;
    }

    template <signed short*>
    constexpr int getRedType() {
        return GL_R16UI;
    }

    template <unsigned short*>
    constexpr int getRedType() {
        return GL_R16I;
    }

    template <int*>
    constexpr int getRedType() {
        return GL_R32UI;
    }

    template <unsigned int*>
    constexpr int getRedType() {
        return GL_R32I;
    }
}

#endif //OPENGLBOILERPLATE_TYPE_H
