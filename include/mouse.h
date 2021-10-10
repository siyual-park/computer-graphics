#ifndef OPENGLBOILERPLATE_MOUSE_H
#define OPENGLBOILERPLATE_MOUSE_H

#include "callback.h"
#include "control.h"

namespace gl {
    struct MousePosition {
        double x;
        double y;
    };

    struct MousePositionOffset {
        double x;
        double y;
    };

    class MousePositionOffsetControl: public Callback<MousePosition>, public Control<MousePositionOffset> {
    public:
        void run(MousePosition value) override;

    protected:
        MousePosition last;
        bool first = true;
    };
}

#endif //OPENGLBOILERPLATE_MOUSE_H
