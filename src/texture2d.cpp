#include "texture2d.h"

namespace gl {
    namespace internal {
        Texture2dSize getTexture2dSizeFromViewport() {
            GLint viewport[4];
            glGetIntegerv(GL_VIEWPORT, viewport);

            auto width = viewport[2] - viewport[0];
            auto height = viewport[3] - viewport[1];

            return Texture2dSize{ .x = width, .y = height };
        }
    }
}
