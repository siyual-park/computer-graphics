#ifndef OPENGLBOILERPLATE_BASE_OBJECT_H
#define OPENGLBOILERPLATE_BASE_OBJECT_H

#include <GL/gl3w.h>

namespace gl {
    class BaseObject {
    public:
        BaseObject();
        ~BaseObject() = default;

        GLuint id;
    };
}

#endif //OPENGLBOILERPLATE_BASE_OBJECT_H
