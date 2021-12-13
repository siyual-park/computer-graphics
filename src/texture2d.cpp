#include "texture2d.h"

using namespace gl;

Texture2d::Texture2d() {
    auto size = internal::getWindowSize();

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, size.width, size.height, 0, GL_RGBA, GL_FLOAT, nullptr);
}

Texture2d::~Texture2d() {
    glDeleteTextures(1, &id);
}
