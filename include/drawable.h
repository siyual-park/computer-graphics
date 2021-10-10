#ifndef OPENGLBOILERPLATE_DRAWABLE_H
#define OPENGLBOILERPLATE_DRAWABLE_H

#include "program.h"

namespace gl {
    class Drawable {
    public:
        virtual void draw(Program &program) {};
    };
}

#endif //OPENGLBOILERPLATE_DRAWABLE_H
