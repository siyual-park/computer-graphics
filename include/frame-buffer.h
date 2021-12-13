#ifndef OPENGLBOILERPLATE_FRAME_BUFFER_H
#define OPENGLBOILERPLATE_FRAME_BUFFER_H

#include "gl-object.h"
#include "window.h"
#include "texture2d.h"

namespace gl {
    class FrameBuffer : public GLObject {
    public:
        explicit FrameBuffer(WindowSize &size);
        ~FrameBuffer();

        void check() const;

        void bind() const;
        void unbind() const;

        void attach(Texture2d &texture2d) const;

        const WindowSize size;

    private:
        GLuint depth_buffer;
    };
}

#endif //OPENGLBOILERPLATE_FRAME_BUFFER_H
