#include "program.h"

#include "cast.h"

gl::Program::Program(): BaseObject{} {
    name = static_cast<unsigned int>(glCreateProgram());
}
gl::Program::~Program() {
    unuse();
    glDeleteProgram(getGLuint(name));
}

void gl::Program::link() {
    glLinkProgram(getGLuint(name));
}
void gl::Program::use() {
    glUseProgram(getGLuint(name));
}
void gl::Program::unuse() {
    glUseProgram(0);
}
