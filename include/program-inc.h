//
// Created by Kakao_Ent on 2021/10/10.
//

#ifndef OPENGLBOILERPLATE_PROGRAM_INC_H
#define OPENGLBOILERPLATE_PROGRAM_INC_H

#include "program.h"

#include "cast.h"

template<unsigned int T>
gl::Program &gl::Program::attach(gl::Shader<T> &shader) {
    glAttachShader(getGLuint(name), getGLuint(shader.name));

    return *this;
}

#endif //OPENGLBOILERPLATE_PROGRAM_INC_H
