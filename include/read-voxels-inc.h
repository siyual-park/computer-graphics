#ifndef OPENGLBOILERPLATE_READ_VOXELS_INC_H
#define OPENGLBOILERPLATE_READ_VOXELS_INC_H

#include "read-voxels.h"

#include <fstream>
#include "endian-type.h"
#include "read-raw.h"

template<class T>
gl::Voxels<T> gl::readVoxels(const std::string &path, ENDIAN_TYPE endian_type) {
    gl::Size size{readSize(path + "/size.txt")};
    gl::Spacing spacing{readSpacing(path + "/spacing.txt")};

    const std::size_t buffer_size = size.width * size.height * size.depth;

    std::unique_ptr<T> read_buffer{std::move(readRaw<T>(path + "/data.raw", buffer_size, endian_type))};

    Voxels<T> voxels{size, spacing};
    gl::internal::copyData<T>(reinterpret_cast<const unsigned char *>(read_buffer.get()), voxels.data, voxels.size.width * voxels.size.height * voxels.size.depth);

    return voxels;
}

#endif //OPENGLBOILERPLATE_READ_VOXELS_INC_H
