#ifndef OPENGLBOILERPLATE_WINDOW_H
#define OPENGLBOILERPLATE_WINDOW_H

#include <set>
#include <string>

#include "callback.h"
#include "mouse.h"

namespace gl {
    struct Size
    {
        int width;
        int height;
    };

    class Window {
    public:
        Window(std::string& title, Size &size);
        Window(std::string&& title, Size &size);
        Window(std::string& title, Size &&size);
        Window(std::string&& title, Size &&size);

        virtual ~Window();

        Size getSize() const noexcept;
        void resize(Size &size);
        void resize(Size &&size);

        virtual void update();
        bool isClose();

        Control<MousePosition> mouse_control;

        void* context;

        std::string title;
        Size size;

    protected:
        void init();
    };
}

#endif //OPENGLBOILERPLATE_WINDOW_H
