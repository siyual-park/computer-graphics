#ifndef OPENGLBOILERPLATE_FRAME_BUFFER_INC_H
#define OPENGLBOILERPLATE_FRAME_BUFFER_INC_H

#include "frame-buffer.h"

template<class T>
void gl::FrameBuffer::attach(Texture2d<T> &texture2d) {
    auto origin_bound = bound;

    bind();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture2d.id, 0);
    check();

    if (!origin_bound) {
        unbind();
    }
}

#endif //OPENGLBOILERPLATE_FRAME_BUFFER_INC_H
