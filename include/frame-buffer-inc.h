#ifndef OPENGLBOILERPLATE_FRAME_BUFFER_INC_H
#define OPENGLBOILERPLATE_FRAME_BUFFER_INC_H

#include "frame-buffer.h"

template<class T>
gl::FrameBuffer::FrameBuffer(Texture2d<T> *texture2d) {
    auto size = internal::getWindowSizeFromViewport();

    glGenRenderbuffers(1, &depth_buffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depth_buffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, size.width, size.height);

    glGenFramebuffers(1, &id);
    glBindFramebuffer(GL_FRAMEBUFFER, id);
    if (texture2d != nullptr) {
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture2d->id, 0);
    }
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth_buffer);

    check();

    glEnable(GL_DEPTH_TEST);

    unbind();
}

#endif //OPENGLBOILERPLATE_FRAME_BUFFER_INC_H
