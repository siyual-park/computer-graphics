#ifndef OPENGLBOILERPLATE_VOXELS_INC_H
#define OPENGLBOILERPLATE_VOXELS_INC_H

#include "voxels.h"
#include <GL/gl3w.h>

template<class T>
gl::Voxels<T>::Voxels(Size size, Spacing spacing):
        size{size}, spacing{spacing} {
    data = new T[size.depth * size.height * size.width];
}

template<class T>
gl::Voxels<T>::Voxels(gl::Voxels<T> &other) noexcept {
    size = other.size;
    spacing = other.spacing;

    data = new T[size.depth * size.height * size.width];
    for (auto i = 0; i < size.depth * size.height * size.width; i++) {
        data[i] = other.data[i];
    }
}

template<class T>
gl::Voxels<T>::Voxels(gl::Voxels<T> &&other) noexcept {
    size = other.size;
    spacing = other.spacing;

    data = other.data;

    other.size = Size{0, 0, 0};
    other.spacing = Spacing{1.0f, 1.0f, 1.0f};
    other.data = nullptr;
}

template<class T>
gl::Voxels<T>::~Voxels() {
    size = Size{0, 0, 0};
    spacing = Spacing{1.0f, 1.0f, 1.0f};

    if (data != nullptr) {
        delete data;
        data = nullptr;
    }
}

#endif //OPENGLBOILERPLATE_VOXELS_INC_H
