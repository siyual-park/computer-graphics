#ifndef OPENGLBOILERPLATE_READ_VOXELS_INC_H
#define OPENGLBOILERPLATE_READ_VOXELS_INC_H

#include "read-voxels.h"

#include <fstream>
#include <limits>

#include "endian-type.h"
#include "read-raw.h"
#include "transfer-function.h"

template<class T>
gl::Voxels<T> gl::readVoxels(const std::string &path, ENDIAN_TYPE endian_type) {
    gl::Size size{readSize(path + "/size.txt")};
    gl::Spacing spacing{readSpacing(path + "/spacing.txt")};

    auto min = (std::numeric_limits<T>)::min();
    auto max = (std::numeric_limits<T>:):max();

    std::size_t tf_origin_size = ((std::size_t) (max - min + 1)) * 4;
    std::size_t tf_size = 256 * 4;

    auto size_diff = tf_origin_size / tf_size;

    std::unique_ptr<unsigned char> tf_origin_buffer{std::move(readRaw<unsigned char>(path + "/tf.raw", tf_origin_size))};
    std::unique_ptr<unsigned char> tf_buffer{new unsigned char[tf_size]};

    for (auto i = 0; i < (tf_size / 4); i++) {
        tf_buffer.get()[4 * i] = tf_origin_buffer.get()[size_diff * 4 * i];
        tf_buffer.get()[4 * i + 1] = tf_origin_buffer.get()[size_diff * 4 * i + 1];
        tf_buffer.get()[4 * i + 2] = tf_origin_buffer.get()[size_diff * 4 * i + 2];
        tf_buffer.get()[4 * i + 3] = tf_origin_buffer.get()[size_diff * 4 * i + 3];
    }

    TransferFunction transfer_function{tf_size};
    gl::internal::copyData<unsigned char>(tf_buffer.get(), transfer_function.data, transfer_function.size);

    const std::size_t buffer_size = size.width * size.height * size.depth;

    std::unique_ptr<T> voxel_buffer{std::move(readRaw<T>(path + "/data.raw", buffer_size, endian_type))};

    Voxels<T> voxels{size, std::move(transfer_function), spacing};
    gl::internal::copyData<T>(voxel_buffer.get(), voxels.data, voxels.size.width * voxels.size.height * voxels.size.depth);

    return voxels;
}

#endif //OPENGLBOILERPLATE_READ_VOXELS_INC_H
