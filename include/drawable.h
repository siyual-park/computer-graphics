#ifndef OPENGLBOILERPLATE_DRAWABLE_H
#define OPENGLBOILERPLATE_DRAWABLE_H

#include "program.h"

namespace gl {
    class Drawable {
    public:
        virtual ~Drawable() = default;

        virtual void draw(Program &program) {};
    };
}

#endif //OPENGLBOILERPLATE_DRAWABLE_H
