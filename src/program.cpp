#include "program.h"

#include "cast.h"

gl::Program::Program(): BaseObject{} {
    name = static_cast<unsigned int>(glCreateProgram());
}
gl::Program::~Program() {
    glDeleteProgram(getGLuint(name));
}

void gl::Program::link() {
    glLinkProgram(getGLuint(name));
}
void gl::Program::use() {
    glUseProgram(getGLuint(name));
}

void gl::Program::setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(getGLuint(this->name), name.c_str()), static_cast<int>(value));
}

void gl::Program::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(getGLuint(this->name), name.c_str()), value);
}

void gl::Program::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(getGLuint(this->name), name.c_str()), value);
}

void gl::Program::setVec2(const std::string &name, const glm::vec2 &value) const {
    glUniform2fv(glGetUniformLocation(getGLuint(this->name), name.c_str()), 1, &value[0]);
}

void gl::Program::setVec3(const std::string &name, const glm::vec3 &value) const {
    glUniform3fv(glGetUniformLocation(getGLuint(this->name), name.c_str()), 1, &value[0]);
}

void gl::Program::setVec4(const std::string &name, const glm::vec4 &value) const {
    glUniform4fv(glGetUniformLocation(getGLuint(this->name), name.c_str()), 1, &value[0]);
}

void gl::Program::setMat2(const std::string &name, const glm::mat2 &mat) const {
    glUniformMatrix2fv(glGetUniformLocation(getGLuint(this->name), name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void gl::Program::setMat3(const std::string &name, const glm::mat3 &mat) const {
    glUniformMatrix3fv(glGetUniformLocation(getGLuint(this->name), name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void gl::Program::setMat4(const std::string &name, const glm::mat4 &mat) const {

}
