#ifndef OPENGLBOILERPLATE_VOLUME_READER_H
#define OPENGLBOILERPLATE_VOLUME_READER_H

#include <string>

#include "volume.h"

namespace gl {
    enum class ENDIAN_TYPE {
        LITTLE,
        BIG
    };

    template<class T>
    class VolumeReader {
    public:
        explicit VolumeReader(std::string &path, ENDIAN_TYPE endian_type = ENDIAN_TYPE::LITTLE);
        explicit VolumeReader(std::string &&path, ENDIAN_TYPE endian_type = ENDIAN_TYPE::LITTLE);
        ~VolumeReader();

        Volume<T> read(Size size, Spacing spacing = {1.0f, 1.0f, 1.0f});

    private:
        std::string path;

        ENDIAN_TYPE endian_type;
    };
}

#include "volume-reader-inc.h"

#endif //OPENGLBOILERPLATE_VOLUME_READER_H
