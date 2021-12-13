#include "program.h"

#include "cast.h"

gl::Program::Program(): BaseObject{} {
    id = static_cast<unsigned int>(glCreateProgram());
}
gl::Program::~Program() {
    disuse();
    glDeleteProgram(getGLuint(id));
}

void gl::Program::link() {
    glLinkProgram(getGLuint(id));
}
void gl::Program::use() {
    glUseProgram(getGLuint(id));
}
void gl::Program::disuse() {
    glUseProgram(0);
}

void gl::Program::setBool(const std::string &name, bool value) const {
    auto id = getLocation(name);
    if (id >= 0) {
        glUniform1i(id, static_cast<int>(value));
    }
}

void gl::Program::setInt(const std::string &name, int value) const {
    auto id = getLocation(name);
    if (id >= 0) {
        glUniform1i(getLocation(name), value);
    }
}

void gl::Program::setFloat(const std::string &name, float value) const {
    auto id = getLocation(name);
    if (id >= 0) {
        glUniform1f(getLocation(name), value);
    }
}

void gl::Program::setVec2(const std::string &name, const glm::vec2 &value) const {
    auto id = getLocation(name);
    if (id >= 0) {
        glUniform2fv(getLocation(name), 1, &value[0]);
    }
}

void gl::Program::setVec3(const std::string &name, const glm::vec3 &value) const {
    auto id = getLocation(name);
    if (id >= 0) {
        glUniform3fv(getLocation(name), 1, &value[0]);
    }
}

void gl::Program::setVec4(const std::string &name, const glm::vec4 &value) const {
    auto id = getLocation(name);
    if (id >= 0) {
        glUniform4fv(getLocation(name), 1, &value[0]);
    }
}

void gl::Program::setMat2(const std::string &name, const glm::mat2 &mat) const {
    auto id = getLocation(name);
    if (id >= 0) {
        glUniformMatrix2fv(getLocation(name), 1, GL_FALSE, &mat[0][0]);
    }
}

void gl::Program::setMat3(const std::string &name, const glm::mat3 &mat) const {
    auto id = getLocation(name);
    if (id >= 0) {
        glUniformMatrix3fv(getLocation(name), 1, GL_FALSE, &mat[0][0]);
    }
}

void gl::Program::setMat4(const std::string &name, const glm::mat4 &mat) const {
    auto id = getLocation(name);
    if (id >= 0) {
        glUniformMatrix4fv(getLocation(name), 1, GL_FALSE, &mat[0][0]);
    }
}

int gl::Program::getLocation(const std::string &name) const {
    return glGetUniformLocation(getGLuint(id), name.c_str());
}
