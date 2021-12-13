#ifndef OPENGLBOILERPLATE_TEXTURE2D_H
#define OPENGLBOILERPLATE_TEXTURE2D_H

#include "gl-object.h"
#include "window.h"

namespace gl {
    class Texture2d : public GLObject {
    public:
        explicit Texture2d(WindowSize &size);
        ~Texture2d();

        const WindowSize size;
    };
}

#endif //OPENGLBOILERPLATE_TEXTURE2D_H
