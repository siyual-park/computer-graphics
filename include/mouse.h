#ifndef OPENGLBOILERPLATE_MOUSE_H
#define OPENGLBOILERPLATE_MOUSE_H

#include "callback.h"

namespace gl {
    struct Position {
        double x;
        double y;
    };

    class MouseCallback : public Callback<Position>{
    };
}

#endif //OPENGLBOILERPLATE_MOUSE_H
