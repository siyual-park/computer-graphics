#include "frame-buffer.h"

using namespace gl;

FrameBuffer::~FrameBuffer() {
    glDeleteRenderbuffers(1, &depth_buffer);
    glDeleteFramebuffers(1, &id);
}

void FrameBuffer::check() const {
    GLenum complete = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (complete != GL_FRAMEBUFFER_COMPLETE) {
        throw std::runtime_error("Can't init frame buffer.");
    }
}

void FrameBuffer::bind() {
    auto size = internal::getWindowSizeFromViewport();
    glBindFramebuffer(GL_FRAMEBUFFER, id);
    glViewport(0, 0, size.width, size.height);
    bound = true;
}

void FrameBuffer::unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    bound = false;
}
