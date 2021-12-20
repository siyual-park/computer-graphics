#include <GL/gl3w.h>

#include "renderer.h"
#include "program.h"

#include "./scene.cpp"

class Renderer: public gl::Renderer {
public:
    explicit Renderer(gl::Window &window): gl::Renderer{window}, scene{*this} {
    }

private:
    void render(double delta_time) override {
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        scene.draw(program);
    }

    gl::Program program;
    Scene scene;
};
