#ifndef OPENGLBOILERPLATE_TYPE_H
#define OPENGLBOILERPLATE_TYPE_H

#include <GL/gl3w.h>

namespace gl {
    template <class T>
    constexpr int getType() {
        return 0;
    }

    template <float>
    constexpr int getType() {
        return GL_FLOAT;
    }

    template <signed float>
    constexpr int getType() {
        return GL_FLOAT;
    }

    template <unsigned float>
    constexpr int getType() {
        return GL_FLOAT;
    }

    template <char>
    constexpr int getType() {
        return GL_BYTE;
    }

    template <signed char>
    constexpr int getType() {
        return GL_BYTE;
    }

    template <unsigned char>
    constexpr int getType() {
        return GL_UNSIGNED_BYTE;
    }

    template <short>
    constexpr int getType() {
        return GL_SHORT;
    }

    template <signed short>
    constexpr int getType() {
        return GL_SHORT;
    }

    template <unsigned short>
    constexpr int getType() {
        return GL_UNSIGNED_SHORT;
    }

    template <int>
    constexpr int getType() {
        return GL_INT;
    }

    template <signed int>
    constexpr int getType() {
        return GL_INT;
    }

    template <unsigned int>
    constexpr int getType() {x
        return GL_UNSIGNED_INT;
    }
}

#endif //OPENGLBOILERPLATE_TYPE_H
