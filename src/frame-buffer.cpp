#include "frame-buffer.h"

using namespace gl;

FrameBuffer::FrameBuffer()
        : texture{nullptr, internal::getTexture2dSizeFromViewport(), GL_RGBA16F, GL_RGBA},
          window_size{internal::getWindowSizeFromViewport()}
{
    auto size = texture.size;

    glGenRenderbuffers(1, &depth_buffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depth_buffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, size.x, size.y);

    glGenFramebuffers(1, &id);
    glBindFramebuffer(GL_FRAMEBUFFER, id);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.id, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth_buffer);

    check();
    glEnable(GL_DEPTH_TEST);

    unbind();
}

FrameBuffer::~FrameBuffer() {
    if (depth_buffer != 0) {
        glDeleteRenderbuffers(1, &depth_buffer);
        depth_buffer = 0;
    }
    if (id != 0) {
        glDeleteFramebuffers(1, &id);
        id = 0;
    }
}

void FrameBuffer::check() const {
    GLenum complete = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (complete != GL_FRAMEBUFFER_COMPLETE) {
        throw std::runtime_error("Can't init frame buffer.");
    }
    GL_ERROR();
}

void FrameBuffer::bind() {
    window_size = internal::getWindowSizeFromViewport();
    auto size = texture.size;

    glBindFramebuffer(GL_FRAMEBUFFER, id);
    glViewport(0, 0, size.x, size.y);
    GL_ERROR();
}

void FrameBuffer::unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, window_size.width, window_size.height);
    GL_ERROR();
}
