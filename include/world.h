#ifndef OPENGLBOILERPLATE_WORLD_H
#define OPENGLBOILERPLATE_WORLD_H

#include "drawable.h"

namespace gl {
    class World: public Drawable {
    public:
        void draw(Program &program) override;

        glm::mat4 mat = glm::mat4(1.0f);
    };
}

#endif //OPENGLBOILERPLATE_WORLD_H
