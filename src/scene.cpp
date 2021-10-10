#include <glm/ext/matrix_clip_space.hpp>
#include "scene.h"

gl::Scene::Scene(Camera &camera, Renderer &renderer): camera{camera}, renderer{renderer}, children{} {
}

void gl::Scene::draw(gl::Program &program) {
    glm::mat4 projection = glm::perspective(
            glm::radians(camera.zoom),
            static_cast<float>(renderer.window.size.width) / static_cast<float>(renderer.window.size.height),
            0.1f,
            100.0f
    );

    program.setMat4("projection", projection);

    glm::mat4 view = camera.getViewMatrix();
    program.setMat4("view", view);

    for (auto &child: children) {
        child.draw(program);
    }
}

void gl::Scene::add(const gl::Drawable& drawable) {
    children.push_back(drawable);
}

gl::SceneRenderer::SceneRenderer(Window &window) : Renderer{window}, program{}, camera{}, scene{Scene{camera, static_cast<Renderer&>(*this)}} {
}

void gl::SceneRenderer::render(double delta_time) {
    program.use();

    scene.draw(program);
}
