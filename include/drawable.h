#ifndef OPENGLBOILERPLATE_DRAWABLE_H
#define OPENGLBOILERPLATE_DRAWABLE_H

#include "program.h"

namespace gl {
    class Drawable {
    public:
        virtual ~Drawable() = default;

        virtual void preDraw(Program &program) {};
        virtual void draw(Program &program) {};
        virtual void postDraw(Program &program) {};
    };
}

#endif //OPENGLBOILERPLATE_DRAWABLE_H
