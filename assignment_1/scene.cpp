#include <glm/ext/matrix_transform.hpp>
#include "scene.h"
#include "camera.h"
#include "model.h"

class Scene: public gl::Scene {
public:
    explicit Scene(gl::Camera &camera, gl::Model &model): gl::Scene{camera} {
        add(model);
    }
};
