#include "initializer.h"
#include "window.h"
#include "model.h"
#include "volume-surface.h"

#include "./renderer.cpp"


int main() {
    gl::setVersion(gl::Version{ .major = 3, .minor =  3 });

    gl::Window window{"Assignment 1", { .width = 1024, .height = 768 }};

    Renderer renderer{window};

    renderer.run();

    return 0;
}