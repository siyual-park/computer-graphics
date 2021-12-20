#ifndef OPENGLBOILERPLATE_TEXTURE2D_INC_H
#define OPENGLBOILERPLATE_TEXTURE2D_INC_H

#include "texture2d.h"
#include "type.h"
#include "error.h"

template<class T>
gl::Texture2d<T>::Texture2d(T *data, Texture2dSize size, int internal_format, int format, int filter):
        size{size}
{
    auto type = getType<T>();

    glGenTextures(1, &id);
    bind();
    glTexImage2D(GL_TEXTURE_2D, 0, internal_format, size.x, size.y, 0, format, type, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);

    unbind();

    GL_ERROR();
}

template<class T>
void gl::Texture2d<T>::bind() {
    glBindTexture(GL_TEXTURE_2D, id);
}

template<class T>
void gl::Texture2d<T>::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

template<class T>
gl::Texture2d<T>::~Texture2d() {
    if (id != 0) {
        glDeleteTextures(1, &id);
        id = 0;
    }
}

#endif //OPENGLBOILERPLATE_TEXTURE2D_INC_H
