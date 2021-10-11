#include "initializer.h"
#include "window.h"
#include "mouse.h"
#include "model.h"

#include "./callback.cpp"
#include "./renderer.cpp"


int main() {
    gl::setVersion(gl::Version{ .major = 3, .minor =  3 });

    gl::Window window{"Assignment 1", { .width = 1024, .height = 768 }};

    gl::Camera camera{};
    gl::Model backpack{"./resources/objects/backpack/backpack.obj"};

    Scene scene{camera, backpack};

    Renderer renderer{window, scene};

    gl::MousePositionOffsetControl  mouse_position_offset_control{};

    PositionChangeCallback position_print_callback{backpack};
    OffsetChangeCallback offset_print_callback{backpack};

    auto &mouse_control = window.mouse_position_control;
    mouse_control.registerCallback(&mouse_position_offset_control);
    mouse_control.registerCallback(&position_print_callback);
    mouse_position_offset_control.registerCallback(&offset_print_callback);

    renderer.run();

    return 0;
}