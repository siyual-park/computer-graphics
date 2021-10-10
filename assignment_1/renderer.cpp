#include <GL/gl3w.h>

#include "renderer.h"
#include "program.h"
#include "shader.h"

class D: public gl::Renderer {
public:
    explicit Renderer(gl::Window &window): gl::Renderer{window}, program{} {
        gl::VertexShader vertex_shader{"./shaders/vertex-shader.glsl"};
        gl::FragmentShader fragment_shader{"./shaders/fragment-shader.glsl"};

        program.attach(vertex_shader);
        program.attach(fragment_shader);

        vertex_shader.compile();
        fragment_shader.compile();

        program.link();
    }

private:
    void render(double delta_time) override {
        program.use();

        static const GLfloat BLACK[] = {0.0f, 0.0f, 0.0f, 0.0f};
        glClearBufferfv(GL_COLOR, 0, BLACK);
    }

    gl::Program program;
};
