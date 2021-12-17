#ifndef OPENGLBOILERPLATE_WORLD_H
#define OPENGLBOILERPLATE_WORLD_H

#include "drawable.h"

namespace gl {
    class World: public Drawable {
    public:
        void preDraw(Program &program) override;
        void draw(Program &program) override;
        void postDraw(Program &program) override;

        glm::mat4 translation = glm::mat4(1.0f);
    };
}

#endif //OPENGLBOILERPLATE_WORLD_H
