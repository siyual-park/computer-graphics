#ifndef OPENGLBOILERPLATE_WINDOW_H
#define OPENGLBOILERPLATE_WINDOW_H

#include <set>
#include <string>

#include "drawable.h"
#include "mouse.h"
#include "event.h"

namespace gl {
    struct WindowSize {
        int width;
        int height;
    };

    class Window: public Drawable {
    public:
        Window(std::string& title, WindowSize &size);
        Window(std::string&& title, WindowSize &size);
        Window(std::string& title, WindowSize &&size);
        Window(std::string&& title, WindowSize &&size);

        ~Window() override;

        WindowSize getSize() const noexcept;
        void resize(WindowSize &size);
        void resize(WindowSize &&size);

        virtual void update();
        bool isClose();

        template<class T>
        void addListener(EventListener<T> listener);

        void preDraw(Program &program) override;

        void* context{};

        std::string title;
        WindowSize size;

        EventEmitter event_emitter{};
    private:
        void init();

        MousePositionOffsetEventProvider mouse_position_offset_event_provider{event_emitter};
    };

    namespace internal {
        WindowSize getWindowSizeFromViewport();
    }
}

#include "window-inc.h"

#endif //OPENGLBOILERPLATE_WINDOW_H
