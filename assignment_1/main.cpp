#include "initializer.h"
#include "window.h"
#include "mouse.h"
#include "model.h"

#include "./callback.cpp"
#include "./renderer.cpp"


int main() {
    gl::setVersion(gl::Version{ .major = 3, .minor =  3 });

    gl::Window window{"Assignment 1", { .width = 1024, .height = 768 }};

    gl::Camera camera{glm::vec3(0.0f, 0.0f, 3.0f)};
    gl::Model backpack{"model", "./resources/objects/backpack/backpack.obj"};

    backpack.scale = glm::vec3(0.5, 0.5, 0.5);

    Scene scene{camera, backpack};
    Renderer renderer{window, scene};

    renderer.run();

    return 0;
}