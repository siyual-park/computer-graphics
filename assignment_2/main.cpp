#include "initializer.h"
#include "window.h"
#include "model.h"

#include "./renderer.cpp"


int main() {
    gl::setVersion(gl::Version{ .major = 3, .minor =  3 });

    gl::Window window{"Assignment 2", { .width = 1024, .height = 768 }};

    gl::Camera camera{glm::vec3(0.0f, 0.0f, 3.0f)};

    camera.zoom = 45.0f;

    Renderer renderer{window, camera};

    renderer.run();

    return 0;
}