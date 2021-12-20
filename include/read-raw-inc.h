#ifndef OPENGLBOILERPLATE_READ_RAW_INC_H
#define OPENGLBOILERPLATE_READ_RAW_INC_H

#include "read-raw.h"
#include <cstring>

template<class T>
std::unique_ptr<T> gl::readRaw(const std::string &path, std::size_t size, ENDIAN_TYPE endian_type) {
    std::ifstream in_file{path, std::ios::binary | std::ios::in};
    if (!in_file.is_open()) {
        throw std::runtime_error{"Can't open file"};
    }

    std::unique_ptr<T> read_buffer{new T[size]};
    std::memset(read_buffer.get(), 0, size * sizeof(T));

    in_file.read(reinterpret_cast<char*>(read_buffer.get()), size * sizeof(T));
    in_file.close();

    if (internal::getEndian() != endian_type) {
        gl::internal::convertEndian<T>(read_buffer.get());
    }

    return read_buffer;
}

#endif //OPENGLBOILERPLATE_READ_RAW_INC_H
