#ifndef OPENGLBOILERPLATE_TEXTURE1D_H
#define OPENGLBOILERPLATE_TEXTURE1D_H

#include <cstddef>

#include "gl-object.h"

namespace gl {
    template <class T>
    class Texture1d : public GLObject {
    public:
        explicit Texture1d(T *data, std::size_t size, int internal_format, int format);
        ~Texture1d();

        void bind();
        void unbind();

        const std::size_t size;
    };
}

#include "texture1d-inc.h"

#endif //OPENGLBOILERPLATE_TEXTURE1D_H
