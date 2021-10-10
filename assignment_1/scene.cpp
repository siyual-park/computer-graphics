#include "scene.h"
#include "camera.h"

class Scene: public gl::Scene {
public:
    explicit Scene(gl::Camera &camera): gl::Scene{camera} {

    }
};
