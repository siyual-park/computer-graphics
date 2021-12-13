#ifndef OPENGLBOILERPLATE_VOXELS_READER_H
#define OPENGLBOILERPLATE_VOXELS_READER_H

#include <string>

#include "voxels.h"

namespace gl {
    enum class ENDIAN_TYPE {
        LITTLE,
        BIG
    };

    template<class T>
    class VoxelsReader {
    public:
        explicit VoxelsReader(std::string &path, ENDIAN_TYPE endian_type = ENDIAN_TYPE::LITTLE);
        explicit VoxelsReader(std::string &&path, ENDIAN_TYPE endian_type = ENDIAN_TYPE::LITTLE);
        ~VoxelsReader();

        Voxels<T> read();

    private:
        Size readSize();
        Spacing readSpacing();

        const std::string path;
        const ENDIAN_TYPE endian_type;
    };
}

#include "voxels-reader-inc.h"

#endif //OPENGLBOILERPLATE_VOXELS_READER_H
