//
// Created by Kakao_Ent on 2021/10/10.
//

#ifndef OPENGLBOILERPLATE_CAST_H
#define OPENGLBOILERPLATE_CAST_H

#include <GL/gl3w.h>

namespace gl {
    template<typename Integer>
    constexpr GLenum getGLenum(Integer value) {
        return static_cast<GLenum>(value);
    }

    template<typename Integer>
    constexpr GLsizeiptr getGLsizeiptr(Integer size) {
        return static_cast<GLsizeiptr>(size);
    }

    template<typename Integer>
    constexpr GLsizei getGLsizei(Integer size) {
        return static_cast<GLsizei>(size);
    }

    template<typename Integer>
    constexpr GLintptr getGLintptr(Integer value) {
        return static_cast<GLintptr>(value);
    }

    template<typename Integer>
    constexpr GLshort getGLshort(Integer value) {
        return static_cast<GLshort>(value);
    }

    template<typename Integer>
    constexpr GLint getGLint(Integer value) {
        return static_cast<GLint>(value);
    }

    template<typename Integer>
    constexpr GLuint getGLuint(Integer value) {
        return static_cast<GLuint>(value);
    }

    template<typename FloatingPoint>
    constexpr GLfloat getGLfloat(FloatingPoint value) {
        return static_cast<GLfloat>(value);
    }

    template<typename FloatingPoint>
    constexpr GLdouble getGLdouble(FloatingPoint value) {
        return static_cast<GLdouble>(value);
    }
}

#endif //OPENGLBOILERPLATE_CAST_H
