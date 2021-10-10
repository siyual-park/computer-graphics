#include "initializer.h"
#include "window.h"

#include "./callback.cpp"
#include "./renderer.cpp"


int main(int argc, char *argv[])
{
    gl::setVersion(gl::Version{ .major = 3, .minor =  3 });

    gl::Window window{"Assignment 1", { .width = 1024, .height = 768 }};

    PositionPrintCallback position_print_callback{};
    auto &mouse_control = window.mouse_position_control;
    mouse_control.registerCallback(static_cast<gl::Callback<gl::MousePosition>*>(&position_print_callback));

    Renderer renderer{window};
    renderer.run();

    return 0;
}