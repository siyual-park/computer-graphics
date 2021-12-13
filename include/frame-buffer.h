#ifndef OPENGLBOILERPLATE_FRAME_BUFFER_H
#define OPENGLBOILERPLATE_FRAME_BUFFER_H

#include "gl-object.h"
#include "window.h"
#include "texture2d.h"

namespace gl {
    class FrameBuffer : public GLObject {
    public:
        explicit FrameBuffer();
        ~FrameBuffer();

        void check() const;

        void bind();
        void unbind();

        void attach(Texture2d &texture2d);
    private:
        GLuint depth_buffer;

        bool bound{false};
    };
}

#endif //OPENGLBOILERPLATE_FRAME_BUFFER_H
