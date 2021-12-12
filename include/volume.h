#ifndef OPENGLBOILERPLATE_VOLUME_H
#define OPENGLBOILERPLATE_VOLUME_H

#include <string>

namespace gl {
    struct Size {
        std::size_t width;
        std::size_t height;
        std::size_t depth;
    };

    struct Spacing {
        float x;
        float y;
        float z;
    };

    template<class T>
    class Volume {
    public:
        Volume(Size size, Spacing spacing = {1.0f, 1.0f, 1.0f});
        Volume(Volume<T> &other) noexcept;
        Volume(Volume<T> &&other) noexcept;
        ~Volume();

        T* data;

        Size size;
        Spacing spacing;
    };
}

#include "volume-inc.h"

#endif //OPENGLBOILERPLATE_VOLUME_H
