#ifndef OPENGLBOILERPLATE_TEXTURE2D_H
#define OPENGLBOILERPLATE_TEXTURE2D_H

#include "gl-object.h"

namespace gl {
    struct Texture2dSize {
        int x;
        int y;
    };

    template <class T>
    class Texture2d : public GLObject {
    public:
        explicit Texture2d(T *data, Texture2dSize size, int internal_format, int format, int filter = GL_NEAREST);
        ~Texture2d();

        void bind();
        void unbind();

        const Texture2dSize size;
    };

    namespace internal {
        Texture2dSize getTexture2dSizeFromViewport();
    }
}

#include "texture2d-inc.h"

#endif //OPENGLBOILERPLATE_TEXTURE2D_H
