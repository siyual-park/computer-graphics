#ifndef OPENGLBOILERPLATE_RENDERER_H
#define OPENGLBOILERPLATE_RENDERER_H

#include "window.h"

namespace gl {

    class Renderer {
    public:
        explicit Renderer(Window& window);
        virtual ~Renderer();

        virtual void run();

        Window &window;
    protected:
        virtual void render(double delta_time);
    };
}

#endif //OPENGLBOILERPLATE_RENDERER_H
