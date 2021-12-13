#ifndef OPENGLBOILERPLATE_GL_OBJECT_H
#define OPENGLBOILERPLATE_GL_OBJECT_H

#include <GL/gl3w.h>

namespace gl {
    class GLObject {
    public:
        GLObject();
        ~GLObject() = default;

        GLuint id;
    };
}

#endif //OPENGLBOILERPLATE_GL_OBJECT_H
