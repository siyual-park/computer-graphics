#include <glm/ext/matrix_clip_space.hpp>

#include "scene.h"
#include <GLFW/glfw3.h>

gl::Scene::Scene(Renderer &renderer, Camera &camera): renderer{renderer}, camera{camera} {
    auto &window = renderer.window;
    auto &event_emitter = window.event_emitter;

    event_emitter.addListener(scene_mouse_position_listener);
    event_emitter.addListener(scene_mouse_button_listener);
    event_emitter.addListener(scene_scroll_listener);
    event_emitter.addListener(scene_mouse_position_offset_listener);
}

void gl::Scene::draw(Program &program) {
    camera.update();
    world.draw(program);

    glm::mat4 projection = glm::perspective(
            glm::radians(camera.zoom),
            static_cast<float>(renderer.window.size.width) / static_cast<float>(renderer.window.size.height),
            0.1f,
            1000.0f
    );
    glm::mat4 view = camera.getViewMatrix();

    program.setMat4("projection", projection);
    program.setMat4("view", view);
    program.setVec3("viewPos", camera.position);

    program.setVec2(
            "ScreenSize",
            glm::vec2(
                    (float)renderer.window.size.width,
                    (float)renderer.window.size.height
            )
    );

    for (auto &child: children) {
        child->draw(program);
    }
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
