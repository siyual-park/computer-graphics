#ifndef OPENGLBOILERPLATE_RENDERER_H
#define OPENGLBOILERPLATE_RENDERER_H


#include "window.h"

namespace gl {

    class Renderer {
    public:
        explicit Renderer(Window& window);
        virtual ~Renderer();

        virtual void run();
        virtual void render(double current_time);

    protected:
        Window &window;
    };
}

#endif //OPENGLBOILERPLATE_RENDERER_H
