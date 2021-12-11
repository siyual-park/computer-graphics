#ifndef OPENGLBOILERPLATE_VOLUME_H
#define OPENGLBOILERPLATE_VOLUME_H

#include <string>

namespace gl {
    struct Spacing {
        float x;
        float y;
        float z;
    };

    template<class T>
    class Volume {
    public:
        Volume(std::size_t width, std::size_t height, std::size_t depth);
        Volume(Volume<T> &other) noexcept;
        Volume(Volume<T> &&other) noexcept;
        ~Volume();

        T** data;

        std::size_t slice;
        std::size_t depth;

        Spacing spacing{1.0f, 1.0f, 1.0f};
    };
}

#include "volume-inc.h"

#endif //OPENGLBOILERPLATE_VOLUME_H
