#ifndef OPENGLBOILERPLATE_TEXTURE1D_INC_H
#define OPENGLBOILERPLATE_TEXTURE1D_INC_H

#include "texture1d.h"
#include "type.h"
#include "error.h"

template<class T>
gl::Texture1d<T>::Texture1d(T *data, std::size_t size, int internal_format, int format, int filter):
        size{size}
{
    auto type = getType<T>();

    glGenTextures(1, &id);
    bind();
    glTexImage1D(GL_TEXTURE_1D, 0, internal_format, size, 0, format, type, data);

    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, filter);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, filter);

    unbind();

    GL_ERROR();
}

template<class T>
void gl::Texture1d<T>::bind() {
    glBindTexture(GL_TEXTURE_1D, id);
}

template<class T>
void gl::Texture1d<T>::unbind() {
    glBindTexture(GL_TEXTURE_1D, 0);
}

template<class T>
gl::Texture1d<T>::~Texture1d() {
    if (id != 0) {
        glDeleteTextures(1, &id);
        id = 0;
    }
}

#endif //OPENGLBOILERPLATE_TEXTURE1D_INC_H
