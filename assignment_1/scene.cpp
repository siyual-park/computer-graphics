#include <glm/ext/matrix_transform.hpp>
#include "scene.h"
#include "camera.h"
#include "model.h"

class Scene: public gl::Scene {
public:
    explicit Scene(gl::Camera &camera, gl::Model &model): gl::Scene{camera} {
        add(model);
    }

    void draw(gl::Renderer &renderer, gl::Program &program) override {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
        program.setMat4("model", model);

        gl::Scene::draw(renderer, program);
    }
};
