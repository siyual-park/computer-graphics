#ifndef OPENGLBOILERPLATE_WINDOW_H
#define OPENGLBOILERPLATE_WINDOW_H

#include <set>
#include <string>

#include "callback.h"
#include "control.h"
#include "mouse.h"

namespace gl {
    struct WindowSize
    {
        int width;
        int height;
    };

    class Window {
    public:
        Window(std::string& title, WindowSize &size);
        Window(std::string&& title, WindowSize &size);
        Window(std::string& title, WindowSize &&size);
        Window(std::string&& title, WindowSize &&size);

        virtual ~Window();

        WindowSize getSize() const noexcept;
        void resize(WindowSize &size);
        void resize(WindowSize &&size);

        virtual void update();
        bool isClose();

        void* context{};

        std::string title;
        WindowSize size;

        Control<MousePosition> mouse_position_control{};
        Control<MouseButtonEvent> mouse_button_control{};

        Control<ScrollOffset> scroll_control{};

        Control<WindowSize> window_size_control{};
    protected:
        void init();
    };
}

#endif //OPENGLBOILERPLATE_WINDOW_H
