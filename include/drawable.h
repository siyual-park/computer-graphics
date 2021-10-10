#ifndef OPENGLBOILERPLATE_DRAWABLE_H
#define OPENGLBOILERPLATE_DRAWABLE_H

#include "program.h"

namespace gl {
    class Drawable {
    public:
        virtual void draw(Program &program) = 0;
    };
}

#endif //OPENGLBOILERPLATE_DRAWABLE_H
