#ifndef OPENGLBOILERPLATE_VOLUME_READER_INC_H
#define OPENGLBOILERPLATE_VOLUME_READER_INC_H

#include <fstream>

#include "volume-reader.h"

namespace gl {
    namespace internal {
        template <class T>
        void copyData(Volume<T> *vol, unsigned char *buffer) noexcept {
            auto converted_buffer = reinterpret_cast<T*>(buffer);
            for (auto i = 0; i < vol->size.width * vol->size.height * vol->size.depth; ++i) {
                vol->data[i] = converted_buffer[i];
            }
        }

        template <typename DATA>
        void convertToBidEndian(DATA *data) noexcept {
            union {
                DATA f;
                unsigned char c8[sizeof(DATA)];
            } source, dest;
            for (auto i = 0; i < sizeof(DATA); ++i) {
                source.f = data[i];
                for (auto k = 0; k < sizeof(DATA); ++k)
                    dest.c8[k] = source.c8[sizeof(DATA) - k - 1];
                data[i] = dest.f;
            }
        }
    }
}

template<class T>
gl::VolumeReader<T>::VolumeReader(std::string &path, ENDIAN_TYPE endian_type):
        path{path},
        endian_type{endian_type} {
}

template<class T>
gl::VolumeReader<T>::VolumeReader(std::string &&path, ENDIAN_TYPE endian_type):
        path{path},
        endian_type{endian_type} {

}

template<class T>
gl::Volume<T> gl::VolumeReader<T>::read(Size size, Spacing spacing) {
    const long buffer_size = size.width * size.height * size.depth;

    std::ifstream in_file{path, std::ios::binary | std::ios::in};
    if (!in_file.is_open()) {
        throw std::runtime_error{"Can't open file"};
    }

    std::unique_ptr<unsigned char> read_buffer{new unsigned char[buffer_size * sizeof(T)]};
    std::memset(read_buffer.get(), 0, sizeof(char) * buffer_size * sizeof(T));

    in_file.read(reinterpret_cast<char*>(read_buffer.get()), buffer_size * sizeof(T));
    if (endian_type == ENDIAN_TYPE::BIG) {
        gl::internal::convertToBidEndian<T>(reinterpret_cast<T*>(read_buffer.get()));
    }

    Volume<T> volume{size, spacing};
    gl::internal::copyData<T>(&volume, read_buffer.get());

    in_file.close();

    return volume;
}

template<class T>
gl::VolumeReader<T>::~VolumeReader() = default;

#endif //OPENGLBOILERPLATE_VOLUME_READER_INC_H
