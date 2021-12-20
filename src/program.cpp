#include "program.h"

#include <memory>
#include "cast.h"

gl::Program::Program(): GLObject{} {
    id = static_cast<unsigned int>(glCreateProgram());
    GL_ERROR();
}
gl::Program::~Program() {
    disuse();
    glDeleteProgram(getGLuint(id));
}

void gl::Program::detaches(int maxCount) {
    GLsizei count{};
    std::unique_ptr<GLuint> shaders{new GLuint[maxCount]};

    glGetAttachedShaders(getGLuint(id), maxCount, &count, shaders.get());
    for (int i = 0; i < count; i++) {
        glDetachShader(getGLuint(id), shaders.get()[i]);
    }

    glBindAttribLocation(getGLuint(id), 0, "VerPos");
    glBindAttribLocation(getGLuint(id), 1, "VerClr");

    GL_ERROR();
}

void gl::Program::link() {
    glLinkProgram(getGLuint(id));
    checkShaderLink();
    GL_ERROR();
}
void gl::Program::use() {
    glUseProgram(getGLuint(id));
    GL_ERROR();
}
void gl::Program::disuse() {
    glUseProgram(0);
    GL_ERROR();
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
    auto location = glGetUniformLocation(getGLuint(id), name.c_str());
    GL_ERROR();
    return location;
}

void gl::Program::checkShaderLink() {
    GLint status;
    glGetProgramiv(getGLuint(id), GL_LINK_STATUS, &status);
    if (GL_FALSE == status) {
        GLint logLen;
        glGetProgramiv(getGLuint(id), GL_INFO_LOG_LENGTH, &logLen);
        if (logLen > 0) {
            GLchar *log = (GLchar *)malloc(logLen);
            GLsizei written;
            glGetProgramInfoLog(getGLuint(id), logLen, &written, log);
            std::string message{log};
            free(log);

            throw std::runtime_error{message};
        }
    }
}
