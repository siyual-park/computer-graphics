#ifndef OPENGLBOILERPLATE_SCENE_H
#define OPENGLBOILERPLATE_SCENE_H

#include <vector>

#include "drawable.h"
#include "camera.h"
#include "renderer.h"
#include "program.h"
#include "mouse.h"

namespace gl {
    class Scene;

    class SceneMousePositionCallback: public Callback<MousePosition> {
    public:
        explicit SceneMousePositionCallback(Scene &scene);
        void run(MousePosition position) override;

    protected:
        Scene &scene;
    };

    class SceneMousePositionOffsetCallback: public Callback<MousePositionOffset> {
    public:
        explicit SceneMousePositionOffsetCallback(Scene &scene);
        void run(MousePositionOffset offset) override;

    protected:
        Scene &scene;
    };

    class SceneMouseButtonCallback: public Callback<MouseButtonEvent> {
    public:
        explicit SceneMouseButtonCallback(Scene &scene);
        void run(MouseButtonEvent event) override;

    protected:
        Scene &scene;
    };

    class SceneScrollCallback: public Callback<ScrollOffset> {
    public:
        explicit SceneScrollCallback(Scene &scene);
        void run(ScrollOffset offset) override;

    protected:
        Scene &scene;
    };

    class Scene: public Drawable {
    public:
        friend SceneMousePositionCallback;
        friend SceneMousePositionOffsetCallback;
        friend SceneMouseButtonCallback;
        friend SceneScrollCallback;

        explicit Scene(Renderer &renderer, Camera &camera);

        virtual void draw(Program &program);

        void add(Drawable& drawable);

    protected:
        virtual void onMouseCursorChange(MousePosition position) {};
        virtual void onMouseCursorChange(MousePositionOffset offset) {};

        virtual void onMouseEnter(int button) {};
        virtual void onMouseRelease(int button) {};

        virtual void onScroll(ScrollOffset offset) {};

        Renderer &renderer;
        Camera &camera;

        std::vector<Drawable*> children{};

    private:
        MousePositionOffsetControl mouse_position_offset_control{};

        SceneMousePositionCallback scene_mouse_position_callback{*this};
        SceneMousePositionOffsetCallback scene_mouse_position_offset_callback{*this};
        SceneMouseButtonCallback scene_mouse_button_callback{*this};
        SceneScrollCallback scene_scroll_callback{*this};
    };
}


#endif //OPENGLBOILERPLATE_SCENE_H
