#ifndef OPENGLBOILERPLATE_TEXTURE3D_H
#define OPENGLBOILERPLATE_TEXTURE3D_H

#include "gl-object.h"

namespace gl {
    struct Texture3dSize {
        int x;
        int y;
        int z;
    };

    template <class T>
    class Texture3d : public GLObject {
    public:
        explicit Texture3d(T *data, Texture3dSize size, int internal_format, int format);
        ~Texture3d();
    };
}

#include "texture3d-inc.h"

#endif //OPENGLBOILERPLATE_TEXTURE3D_H
