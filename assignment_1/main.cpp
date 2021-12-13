#include "initializer.h"
#include "window.h"
#include "model.h"

#include "./renderer.cpp"


int main() {
    gl::setVersion(gl::Version{ .major = 3, .minor =  3 });

    gl::Window window{"Assignment 1", { .width = 1024, .height = 768 }};

    gl::Camera camera{glm::vec3(0.0f, 0.0f, 3.0f)};
    gl::Model backpack{"model", "./resources/objects/backpack/backpack.obj"};

    camera.zoom = 45.0f;
    backpack.scale = glm::vec3(0.2, 0.2, 0.2);

    Renderer renderer{window, camera, backpack};

    renderer.run();

    return 0;
}