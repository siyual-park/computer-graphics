#include <GL/gl3w.h>

#include "renderer.h"
#include "program.h"
#include "shader.h"

class Renderer: public gl::Renderer {
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
    void render(double current_time) override {
        program.use();

        static const GLfloat RED[] = {1.0f, .0f, .0f, 1.0f};
        glClearBufferfv(GL_COLOR, 0, RED);

        program.unuse();
    }

    gl::Program program;
};
