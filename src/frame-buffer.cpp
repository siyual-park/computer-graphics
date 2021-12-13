#include "frame-buffer.h"

using namespace gl;

FrameBuffer::FrameBuffer(WindowSize &size): size{size} {
    glGenRenderbuffers(1, &depth_buffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depth_buffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, size.width, size.height);

    glGenFramebuffers(1, &id);
    glBindFramebuffer(GL_FRAMEBUFFER, id);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth_buffer);

    check();

    glEnable(GL_DEPTH_TEST);

    unbind();
}

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

void FrameBuffer::bind() const {
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, id);
    glViewport(0, 0, size.width, size.height);
}

void FrameBuffer::unbind() const {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::attach(Texture2d &texture2d) const {
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture2d.id, 0);
    check();
}