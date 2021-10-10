#include <GL/gl3w.h>

#include "renderer.h"
#include "program.h"
#include "shader.h"

class Renderer: public gl::Renderer {
public:
    explicit Renderer(gl::Window &window): gl::Renderer{window}, program{} {
        gl::VertexShader vertex_shader{"./shader/vertex-shader.glsl"};
        gl::FragmentShader fragment_shader{"./shader/fragment-shader.glsl"};

        vertex_shader.compile();
        fragment_shader.compile();

        program.attach(vertex_shader)
                .attach(fragment_shader)
                .link();
    }

private:
    void render(double current_time) override {
        static const GLfloat RED[] = {1.0f, .0f, .0f, 1.0f};
        glClearBufferfv(GL_COLOR, 0, RED);
    }

    gl::Program program;
};
