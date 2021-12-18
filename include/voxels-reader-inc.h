#ifndef OPENGLBOILERPLATE_VOXELS_READER_INC_H
#define OPENGLBOILERPLATE_VOXELS_READER_INC_H

#include <fstream>

#include "voxels-reader.h"
#include "endian-type.h"

template<class T>
gl::VoxelsReader<T>::VoxelsReader(std::string &path, ENDIAN_TYPE endian_type):
        path{path},
        endian_type{endian_type} {
}

template<class T>
gl::VoxelsReader<T>::VoxelsReader(std::string &&path, ENDIAN_TYPE endian_type):
        path{path},
        endian_type{endian_type} {
}

template<class T>
gl::Voxels<T> gl::VoxelsReader<T>::read() {
    gl::Size size{readSize()};
    gl::Spacing spacing{readSpacing()};

    const long buffer_size = size.width * size.height * size.depth;

    std::ifstream in_file{path + "/data.raw", std::ios::binary | std::ios::in};
    if (!in_file.is_open()) {
        throw std::runtime_error{"Can't open file"};
    }

    std::unique_ptr<unsigned char> read_buffer{new unsigned char[buffer_size * sizeof(T)]};
    std::memset(read_buffer.get(), 0, sizeof(char) * buffer_size * sizeof(T));

    in_file.read(reinterpret_cast<char*>(read_buffer.get()), buffer_size * sizeof(T));
    in_file.close();

    if (endian_type == ENDIAN_TYPE::BIG) {
        gl::internal::convertToBidEndian<T>(reinterpret_cast<T*>(read_buffer.get()));
    }

    Voxels<T> voxels{size, spacing};
    gl::internal::copyData<T>(read_buffer.get(), voxels.data, voxels.size.width * voxels.size.height * voxels.size.depth);

    return voxels;
}

template<class T>
gl::Size gl::VoxelsReader<T>::readSize() {
    std::ifstream in_file{path + "/size.txt", std::ios::in};
    if (!in_file.is_open()) {
        throw std::runtime_error{"Can't open file"};
    }

    std::size_t width, height, depth;
    in_file >> width >> height >> depth;

    in_file.close();

    return gl::Size{width, height, depth};
}

template<class T>
gl::Spacing gl::VoxelsReader<T>::readSpacing() {
    std::ifstream in_file{path + "/spacing.txt", std::ios::in};
    if (!in_file.is_open()) {
        throw std::runtime_error{"Can't open file"};
    }

    float x, y, z;
    in_file >> x >> y >> z;

    in_file.close();

    return gl::Spacing{x, y, z};
}

template<class T>
gl::VoxelsReader<T>::~VoxelsReader() = default;

#endif //OPENGLBOILERPLATE_VOXELS_READER_INC_H
