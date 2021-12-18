#ifndef OPENGLBOILERPLATE_READ_VOXELS_H
#define OPENGLBOILERPLATE_READ_VOXELS_H

#include <string>

#include "voxels.h"
#include "endian-type.h"

namespace gl {
    template<class T>
    Voxels<T> readVoxels(const std::string &path, ENDIAN_TYPE endian_type = ENDIAN_TYPE::LITTLE);

    Size readSize(const std::string &path);
    Spacing readSpacing(const std::string &path);
}

#include "read-voxels-inc.h"

#endif //OPENGLBOILERPLATE_READ_VOXELS_H
