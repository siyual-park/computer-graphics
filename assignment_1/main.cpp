#include "initializer.h"
#include "window.h"
#include "mouse.h"

#include "./callback.cpp"
#include "./renderer.cpp"


int main() {
    gl::setVersion(gl::Version{ .major = 3, .minor =  3 });

    gl::Window window{"Assignment 1", { .width = 1024, .height = 768 }};

    PositionPrintCallback position_print_callback{};
    gl::MousePositionOffsetControl  mouse_position_offset_control{};

    auto &mouse_control = window.mouse_position_control;
    mouse_control.registerCallback(static_cast<gl::Callback<gl::MousePosition>*>(&position_print_callback));
    mouse_control.registerCallback(static_cast<gl::Callback<gl::MousePosition>*>(&mouse_position_offset_control));

    gl::Camera camera{};
    Scene scene{camera};

    Renderer renderer{window, scene};
    renderer.run();

    return 0;
}