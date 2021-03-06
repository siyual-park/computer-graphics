#include <glm/ext/matrix_clip_space.hpp>

#include "scene.h"
#include <GLFW/glfw3.h>

gl::Scene::Scene(Renderer &renderer): renderer{renderer} {
    auto &window = renderer.window;
    auto &event_emitter = window.event_emitter;

    event_emitter.addListener(scene_mouse_position_listener);
    event_emitter.addListener(scene_mouse_button_listener);
    event_emitter.addListener(scene_scroll_listener);
    event_emitter.addListener(scene_mouse_position_offset_listener);
}

void gl::Scene::preDraw(gl::Program &program) {
    for (auto &child: children) {
        child->preDraw(program);
    }
}


void gl::Scene::draw(Program &program) {
    preDraw(program);

    for (auto &child: children) {
        child->draw(program);
    }

    postDraw(program);
}

void gl::Scene::postDraw(gl::Program &program) {
    for (auto &child: children) {
        child->postDraw(program);
    }

    program.disuse();
}

void gl::Scene::add(gl::Drawable& drawable) {
    children.push_back(&drawable);
}

gl::SceneMousePositionEventListener::SceneMousePositionEventListener(gl::Scene &scene): scene{scene} {
}

void gl::SceneMousePositionEventListener::on(gl::MousePositionEvent position) {
    scene.onMouseCursorChange(position);
}

gl::SceneMousePositionOffsetEventListener::SceneMousePositionOffsetEventListener(gl::Scene &scene): scene{scene} {
}

void gl::SceneMousePositionOffsetEventListener::on(gl::MousePositionOffsetEvent offset) {
    scene.onMouseCursorChange(offset);
}

gl::SceneMouseButtonEventListener::SceneMouseButtonEventListener(gl::Scene &scene): scene{scene} {
}

void gl::SceneMouseButtonEventListener::on(gl::MouseButtonEvent event) {
    if (event.action == GLFW_PRESS) {
        scene.onMouseEnter(event.button);
    }
    if (event.action == GLFW_RELEASE) {
        scene.onMouseRelease(event.button);
    }
}

gl::SceneScrollEventListener::SceneScrollEventListener(gl::Scene &scene): scene{scene} {

}

void gl::SceneScrollEventListener::on(gl::ScrollOffset offset) {
    scene.onScroll(offset);
}
