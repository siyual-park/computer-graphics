#include <GL/gl3w.h>

#include "renderer.h"
#include "program.h"
#include "shader.h"

#include "./scene.cpp"

class Renderer: public gl::Renderer {
public:
    explicit Renderer(gl::Window &window): gl::Renderer{window}, scene{*this} {
        glEnable(GL_DEPTH_TEST);

        gl::VertexShader vertex_shader{"./shaders/vertex-shader.glsl"};
        gl::FragmentShader fragment_shader{"./shaders/fragment-shader.glsl"};

        vertex_shader.compile();
        fragment_shader.compile();

        program.attach(vertex_shader);
        program.attach(fragment_shader);

        program.link();
    }

private:
    void render(double delta_time) override {
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        program.use();
        scene.draw(program);
    }

    gl::Program program;
    Scene scene;
};
