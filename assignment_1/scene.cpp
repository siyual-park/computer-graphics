#include <glm/ext/matrix_transform.hpp>
#include "scene.h"
#include "camera.h"
#include "model.h"

class Scene: public gl::Scene {
public:
    explicit Scene(gl::Renderer &renderer, gl::Camera &camera, gl::Model &model): gl::Scene{renderer, camera} {
        add(model);
    }

    void onMouseChange(gl::MousePosition position) override {

    }

    void onMouseChange(gl::MousePositionOffset offset) override {

    }
};
