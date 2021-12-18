#ifndef OPENGLBOILERPLATE_TEXTURE3D_INC_H
#define OPENGLBOILERPLATE_TEXTURE3D_INC_H

#include "texture3d.h"
#include "type.h"

template<class T>
gl::Texture3d<T>::Texture3d(T *data, Texture3dSize size, int internal_format, int format, int filter):
        size{size}
{
    auto type = getType<T>();

    glGenTextures(1, &id);
    bind();
    glTexImage3D(GL_TEXTURE_3D, 0, internal_format, size.x, size.y, size.z, 0, format, type, data);

    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, filter);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, filter);

    unbind();

    GL_ERROR();
}

template<class T>
void gl::Texture3d<T>::bind() {
    glBindTexture(GL_TEXTURE_3D, id);
}

template<class T>
void gl::Texture3d<T>::unbind() {
    glBindTexture(GL_TEXTURE_3D, 0);
}

template<class T>
gl::Texture3d<T>::~Texture3d() {
    if (id != 0) {
        glDeleteTextures(1, &id);
        id = 0;
    }
}

#endif //OPENGLBOILERPLATE_TEXTURE3D_INC_H
