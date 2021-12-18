#ifndef OPENGLBOILERPLATE_SCENE_H
#define OPENGLBOILERPLATE_SCENE_H

#include <vector>

#include "drawable.h"
#include "camera.h"
#include "renderer.h"
#include "program.h"
#include "world.h"
#include "mouse.h"

namespace gl {
    class Scene;

    class SceneMousePositionEventListener: public EventListener<MousePositionEvent> {
    public:
        explicit SceneMousePositionEventListener(Scene &scene);
        void on(MousePositionEvent position) override;

    protected:
        Scene &scene;
    };

    class SceneMousePositionOffsetEventListener: public EventListener<MousePositionOffsetEvent> {
    public:
        explicit SceneMousePositionOffsetEventListener(Scene &scene);
        void on(MousePositionOffsetEvent offset) override;

    protected:
        Scene &scene;
    };

    class SceneMouseButtonEventListener: public EventListener<MouseButtonEvent> {
    public:
        explicit SceneMouseButtonEventListener(Scene &scene);
        void on(MouseButtonEvent event) override;

    protected:
        Scene &scene;
    };

    class SceneScrollEventListener: public EventListener<ScrollOffset> {
    public:
        explicit SceneScrollEventListener(Scene &scene);
        void on(ScrollOffset offset) override;

    protected:
        Scene &scene;
    };

    class Scene: public Drawable {
    public:
        friend SceneMousePositionEventListener;
        friend SceneMousePositionOffsetEventListener;
        friend SceneMouseButtonEventListener;
        friend SceneScrollEventListener;

        explicit Scene(Renderer &renderer);

        void preDraw(Program &program) override;
        void draw(Program &program) override;
        void postDraw(Program &program) override;

        void add(Drawable& drawable);

    protected:
        virtual void onMouseCursorChange(MousePositionEvent position) {};
        virtual void onMouseCursorChange(MousePositionOffsetEvent offset) {};

        virtual void onMouseEnter(int button) {};
        virtual void onMouseRelease(int button) {};

        virtual void onScroll(ScrollOffset offset) {};

        Renderer &renderer;
        std::vector<Drawable*> children{};

    private:
        SceneMousePositionEventListener scene_mouse_position_listener{*this};
        SceneMousePositionOffsetEventListener scene_mouse_position_offset_listener{*this};
        SceneMouseButtonEventListener scene_mouse_button_listener{*this};
        SceneScrollEventListener scene_scroll_listener{*this};
    };
}


#endif //OPENGLBOILERPLATE_SCENE_H
