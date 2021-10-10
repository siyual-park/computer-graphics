#ifndef OPENGLBOILERPLATE_SCENE_H
#define OPENGLBOILERPLATE_SCENE_H

#include <vector>

#include "drawable.h"
#include "camera.h"
#include "renderer.h"
#include "program.h"

namespace gl {
    class Scene: public Drawable {
    public:
        explicit Scene(Camera &camera, Renderer &renderer);

        void draw(Program &program) override;

        void add(const Drawable& drawable);

    protected:
        Camera &camera;
        Renderer &renderer;

        std::vector<Drawable> children;
    };

    class SceneRenderer: public Renderer {
    public:
        explicit SceneRenderer(Window& window);

    protected:
        void render(double delta_time) override;

        Camera camera;
        Scene scene;
        Program program;
    };
}


#endif //OPENGLBOILERPLATE_SCENE_H
