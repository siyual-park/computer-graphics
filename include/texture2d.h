#ifndef OPENGLBOILERPLATE_TEXTURE2D_H
#define OPENGLBOILERPLATE_TEXTURE2D_H

#include "gl-object.h"
#include "window.h"

namespace gl {
    class Texture2d : public GLObject {
    public:
        explicit Texture2d();
        ~Texture2d();
    };
}

#endif //OPENGLBOILERPLATE_TEXTURE2D_H
