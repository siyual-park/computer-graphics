#ifndef OPENGLBOILERPLATE_FRAME_BUFFER_H
#define OPENGLBOILERPLATE_FRAME_BUFFER_H

#include "gl-object.h"
#include "window.h"
#include "texture2d.h"

namespace gl {
    class FrameBuffer : public GLObject {
    public:
        template<class T>
        explicit FrameBuffer(Texture2d<T> *texture2d = nullptr);
        ~FrameBuffer();

        void check() const;

        void bind();
        void unbind();
    private:
        GLuint depth_buffer;

        bool bound{false};
    };
}

#include "frame-buffer-inc.h"

#endif //OPENGLBOILERPLATE_FRAME_BUFFER_H
