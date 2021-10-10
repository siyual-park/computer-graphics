#ifndef OPENGLBOILERPLATE_MOUSE_H
#define OPENGLBOILERPLATE_MOUSE_H

#include "callback.h"

namespace gl {
    struct MousePosition {
        double x;
        double y;
    };

    class MouseCallback : public Callback<MousePosition>{
    };
}

#endif //OPENGLBOILERPLATE_MOUSE_H
