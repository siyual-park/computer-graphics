#ifndef OPENGLBOILERPLATE_TYPE_H
#define OPENGLBOILERPLATE_TYPE_H

#include <GL/gl3w.h>

namespace gl {
    template <typename T>
    constexpr int getType(T empty = (T) 0) {
        return 0;
    }

    template <typename T>
    constexpr int getRedType(T empty = (T) 0) {
        return 0;
    }

    template <typename T>
    constexpr int getRedFormat(T empty = (T) 0) {
        return 0;
    }

    template <>
    constexpr int getType<float>(float empty) {
        return GL_FLOAT;
    }

    template <>
    constexpr int getType<signed char>(signed char empty) {
        return GL_BYTE;
    }

    template <>
    constexpr int getType<unsigned char>(unsigned char empty) {
        return GL_UNSIGNED_BYTE;
    }

    template <>
    constexpr int getType<signed short>(signed short empty) {
        return GL_SHORT;
    }

    template <>
    constexpr int getType<unsigned short>(unsigned short empty) {
        return GL_UNSIGNED_SHORT;
    }

    template <>
    constexpr int getType<signed int>(signed int empty) {
        return GL_INT;
    }

    template <>
    constexpr int getType<unsigned int>(unsigned int empty) {
        return GL_UNSIGNED_INT;
    }

    template <>
    constexpr int getRedType<float>(float empty) {
        return GL_R16F;
    }

    template <>
    constexpr int getRedType<signed char>(signed char empty) {
        return GL_R8_SNORM;
    }

    template <>
    constexpr int getRedType<unsigned char>(unsigned char empty) {
        return GL_R8;
    }

    template <>
    constexpr int getRedType<signed short>(signed short empty) {
        return GL_R16I;
    }

    template <>
    constexpr int getRedType<unsigned short>(unsigned short empty) {
        return GL_R16UI;
    }

    template <>
    constexpr int getRedType<signed int>(signed int empty) {
        return GL_R32I;
    }

    template <>
    constexpr int getRedType<unsigned int>(unsigned int empty) {
        return GL_R32UI;
    }

    template <>
    constexpr int getRedFormat<float>(float empty) {
        return GL_RED;
    }

    template <>
    constexpr int getRedFormat<signed char>(signed char empty) {
        return GL_RED;
    }

    template <>
    constexpr int getRedFormat<unsigned char>(unsigned char empty) {
        return GL_RED;
    }

    template <>
    constexpr int getRedFormat<signed short>(signed short empty) {
        return GL_RED_INTEGER;
    }

    template <>
    constexpr int getRedFormat<unsigned short>(unsigned short empty) {
        return GL_RED_INTEGER;
    }

    template <>
    constexpr int getRedFormat<signed int>(signed int empty) {
        return GL_RED_INTEGER;
    }

    template <>
    constexpr int getRedFormat<unsigned int>(unsigned int empty) {
        return GL_RED_INTEGER;
    }
}

#endif //OPENGLBOILERPLATE_TYPE_H
