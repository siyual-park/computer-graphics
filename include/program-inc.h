#ifndef OPENGLBOILERPLATE_PROGRAM_INC_H
#define OPENGLBOILERPLATE_PROGRAM_INC_H

#include "program.h"

#include "cast.h"

template<unsigned int T>
gl::Program &gl::Program::attach(gl::Shader<T> &shader) {
    glAttachShader(getGLuint(id), getGLuint(shader.id));

    return *this;
}

#endif //OPENGLBOILERPLATE_PROGRAM_INC_H
