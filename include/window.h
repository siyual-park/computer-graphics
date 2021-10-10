#ifndef OPENGLBOILERPLATE_WINDOW_H
#define OPENGLBOILERPLATE_WINDOW_H

#include <set>
#include <string>

#include "initializer.h"
#include "callback.h"
#include "control.h"
#include "mouse.h"

namespace gl {
    struct Size
    {
        int width;
        int height;
    };

    class Window {
    public:
        Window(Initializer &initializer, std::string& title, Size &size);
        Window(Initializer &initializer, std::string&& title, Size &size);
        Window(Initializer &initializer, std::string& title, Size &&size);
        Window(Initializer &initializer, std::string&& title, Size &&size);

        virtual ~Window();

        Size getSize() const noexcept;
        void resize(Size &size);
        void resize(Size &&size);

        virtual void update();
        bool isClose();

        Control<MousePosition> &getMousePositionControl();

        void* context;

        std::string title;
        Size size;

    protected:
        void init();

        Control<MousePosition> mouse_position_control;
    };
}

#endif //OPENGLBOILERPLATE_WINDOW_H
