#ifndef OPENGLBOILERPLATE_SHADER_INC_H
#define OPENGLBOILERPLATE_SHADER_INC_H

#include "shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <GL/gl3w.h>

#include "cast.h"
#include "error.h"

template <unsigned int T>
std::string getShaderSource(gl::Shader<T> &shader) {
    std::string shader_source;
    std::ifstream shader_stream{shader.path.c_str()};

    if (shader_stream.is_open()) {
        std::stringstream string_stream{};

        string_stream << shader_stream.rdbuf();
        shader_source = string_stream.str();

        shader_stream.close();
    } else {
        errorHandle(gl::Error::GL, "Can't read shader's source file");
    }

    return shader_source;
}


template <unsigned int T>
void init(gl::Shader<T> &shader, std::string &path) {
    shader.id = glCreateShader(shader.Type);

    const std::string& shader_source{getShaderSource(shader)};
    const char *p_shader_source = shader_source.data();
    glShaderSource(gl::getGLuint(shader.id), 1, &p_shader_source, nullptr);
}

template<unsigned int T>
gl::Shader<T>::Shader(std::string &path): path{path}, BaseObject{} {
    init(*this, path);
}

template <unsigned int T>
gl::Shader<T>::Shader(std::string &&path): path{path}, BaseObject{} {
    init(*this, path);
}

template<unsigned int T>
gl::Shader<T>::~Shader() {
    glDeleteShader(getGLuint(id));
}

template<unsigned int T>
void gl::Shader<T>::compile() {
    if (is_compiled) {
        return;
    }

    glCompileShader(getGLuint(id));

    int result;
    int log_length;

    glGetShaderiv(getGLuint(id), GL_COMPILE_STATUS, &result);
    glGetShaderiv(getGLuint(id), GL_INFO_LOG_LENGTH, &log_length);

    if (log_length > 0) {
        std::string error_message{};
        error_message.resize(log_length + 1);

        glGetShaderInfoLog(getGLuint(id),
                           log_length,
                           nullptr,
                           const_cast<GLchar *>(error_message.c_str()));
        errorHandle(Error::GL, error_message);
        return;
    }

    is_compiled = true;
}

template<unsigned int T>
bool gl::Shader<T>::isCompiled() {
    return is_compiled;
}


#endif //OPENGLBOILERPLATE_SHADER_INC_H
