#include <glm/ext/matrix_clip_space.hpp>
#include "scene.h"

gl::Scene::Scene(Camera &camera): camera{camera}, children{} {
}

void gl::Scene::draw(Renderer &renderer, Program &program) {
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
