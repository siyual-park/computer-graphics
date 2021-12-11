#ifndef OPENGLBOILERPLATE_VOLUME_INC_H
#define OPENGLBOILERPLATE_VOLUME_INC_H

#include "volume.h"

template<class T>
gl::Volume<T>::Volume(std::size_t width, std::size_t height, std::size_t depth):
        slice{width * height}, depth{depth} {
    data = new T*[depth];
    for (auto i = 0; i < depth; i++) {
        data[i] = new T[slice];
    }
}

template<class T>
gl::Volume<T>::Volume(gl::Volume<T> &other) noexcept {
    slice = other.slice;
    depth = other.depth;

    data = new T*[depth];
    for (auto i = 0; i < depth; i++) {
        data[i] = new T[slice];

        for (auto j = 0; j < slice; j++) {
            data[i][j] = other.data[i][j];
        }
    }
}

template<class T>
gl::Volume<T>::Volume(gl::Volume<T> &&other) noexcept {
    slice = other.slice;
    depth = other.depth;

    data = other.data;

    other.slice = 0;
    other.depth = 0;
    other.data = nullptr;
}

template<class T>
gl::Volume<T>::~Volume() {
    if (data != nullptr) {
        for (auto i = 0; i < depth; i++) {
            delete data[i];
            data[i] = nullptr;
        }
        delete data;
        data = nullptr;
    }
}

#endif //OPENGLBOILERPLATE_VOLUME_INC_H
