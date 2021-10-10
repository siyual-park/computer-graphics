#include <GL/gl3w.h>

#include "renderer.h"

class Renderer: public gl::Renderer {
public:
    explicit Renderer(gl::Window &window): gl::Renderer{window} {}

protected:
    void render(double current_time) override {
        static const GLfloat RED[] = {1.0f, .0f, .0f, 1.0f};
        glClearBufferfv(GL_COLOR, 0, RED);
    }
};
