#ifdef __APPLE__
/* Defined before OpenGL and GLUT includes to avoid deprecation messages */
#define GL_SILENCE_DEPRECATION
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#else
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#endif

#include <iostream>

#include "initializer.h"
#include "window.h"
#include "callback.h"
#include "mouse.h"
#include "renderer.h"

class PositionPrintCallback: public gl::Callback<gl::MousePosition> {
public:
    void run(gl::MousePosition position) override {
        std::cout << "X: " << position.x << ", Y: " << position.y << std::endl;
    }
};

class Renderer: public gl::Renderer {
public:
    explicit Renderer(gl::Window &window): gl::Renderer{window} {}

protected:
    void render(double current_time) override {
        static const GLfloat RED[] = {1.0f, .0f, .0f, 1.0f};
        glClearBufferfv(GL_COLOR, 0, RED);
    }
};

int main(int argc, char *argv[])
{
    gl::Initializer initializer{{ .major = 3, .minor =  3 }};
    initializer.init();

    gl::Window window{initializer, "OpenGL", { .width = 1024, .height = 768 }};

    auto &mouse_control = window.getMousePositionControl();

    PositionPrintCallback position_print_callback{};
    mouse_control.registerCallback(reinterpret_cast<gl::Callback<gl::MousePosition>*>(&position_print_callback));

    Renderer renderer{window};

    renderer.run();

    return 0;
}