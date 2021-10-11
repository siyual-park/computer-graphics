#include <glm/ext/matrix_clip_space.hpp>
#include "scene.h"

gl::Scene::Scene(Renderer &renderer, Camera &camera): renderer{renderer}, camera{camera}, children{}, scene_mouse_position_callback{*this}, scene_mouse_position_offset_callback{*this} {
    auto &window = renderer.window;
    auto &mouse_control = window.mouse_position_control;

    mouse_control.registerCallback(&mouse_position_offset_control);
    mouse_control.registerCallback(&scene_mouse_position_callback);
    mouse_position_offset_control.registerCallback(&scene_mouse_position_offset_callback);
}

void gl::Scene::draw(Program &program) {
    camera.update();

    glm::mat4 projection = glm::perspective(
            glm::radians(camera.zoom),
            static_cast<float>(renderer.window.size.width) / static_cast<float>(renderer.window.size.height),
            0.1f,
            1000.0f
    );
    glm::mat4 view = camera.getViewMatrix();

    program.setMat4("projection", projection);
    program.setMat4("view", view);

    for (auto &child: children) {
        child->draw(program);
    }
}

void gl::Scene::add(gl::Drawable& drawable) {
    children.push_back(&drawable);
}

gl::SceneMousePositionCallback::SceneMousePositionCallback(gl::Scene &scene): scene{scene} {

}

void gl::SceneMousePositionCallback::run(gl::MousePosition position) {
    scene.onMouseCursorChange(position);
}

gl::SceneMousePositionOffsetCallback::SceneMousePositionOffsetCallback(gl::Scene &scene): scene{scene} {
}

void gl::SceneMousePositionOffsetCallback::run(gl::MousePositionOffset offset) {
    scene.onMouseCursorChange(offset);
}
