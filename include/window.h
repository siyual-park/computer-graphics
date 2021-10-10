#ifndef OPENGLBOILERPLATE_WINDOW_H
#define OPENGLBOILERPLATE_WINDOW_H

#include <string>

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

    protected:
        std::string title;
        Size size;

        void* context;

        void init();
    };
}

#endif //OPENGLBOILERPLATE_WINDOW_H
