#ifndef OPENGLBOILERPLATE_SCENE_H
#define OPENGLBOILERPLATE_SCENE_H

#include <vector>

#include "drawable.h"
#include "camera.h"
#include "renderer.h"
#include "program.h"

namespace gl {
    class Scene {
    public:
        explicit Scene(Camera &camera);

        virtual void draw(Renderer &renderer, Program &program);

        void add(const Drawable& drawable);

    protected:
        Camera &camera;
        std::vector<Drawable> children;
    };
}


#endif //OPENGLBOILERPLATE_SCENE_H
