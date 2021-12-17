#include <GL/gl3w.h>

#include "renderer.h"
#include "program.h"

#include "./scene.cpp"

class Renderer: public gl::Renderer {
public:
    explicit Renderer(gl::Window &window): gl::Renderer{window}, scene{*this} {
        glEnable(GL_DEPTH_TEST);
    }

private:
    void render(double delta_time) override {
        glEnable(GL_DEPTH_TEST);
        GL_ERROR();

        scene.draw(program);
        program.use();
    }

    gl::Program program;
    Scene scene;
};
