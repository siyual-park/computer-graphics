#ifndef OPENGLBOILERPLATE_PROGRAM_INC_H
#define OPENGLBOILERPLATE_PROGRAM_INC_H

#include "program.h"

#include "cast.h"

template<unsigned int T>
void gl::Program::attach(Shader<T> &shader) {
    glAttachShader(getGLuint(id), getGLuint(shader.id));
    GL_ERROR();
}

template<unsigned int T>
void gl::Program::detach(Shader<T> &shader) {
    glDetachShader(getGLuint(id), getGLuint(shader.id));
    GL_ERROR();
}

#endif //OPENGLBOILERPLATE_PROGRAM_INC_H
