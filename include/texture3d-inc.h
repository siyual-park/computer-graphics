#ifndef OPENGLBOILERPLATE_TEXTURE3D_INC_H
#define OPENGLBOILERPLATE_TEXTURE3D_INC_H

#include "texture3d.h"
#include "type.h"

template<class T>
gl::Texture3d<T>::Texture3d(T *data, Texture3dSize size, int internal_format, int format) {
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_3D, id);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);
    glTexImage3D(GL_TEXTURE_3D, 0, internal_format, size.x, size.y, size.z, 0, format, getType<T*>(), data);
}

template<class T>
gl::Texture3d<T>::~Texture3d() {
    if (id != 0) {
        glDeleteTextures(1, &id);
        id = 0;
    }
}


#endif //OPENGLBOILERPLATE_TEXTURE3D_INC_H
