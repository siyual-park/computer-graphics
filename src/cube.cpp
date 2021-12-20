#include "cube.h"

#include <glm/ext/matrix_transform.hpp>

using namespace gl;

const GLfloat g_vertex_buffer[] = {
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, 0.5f, -0.5f,
        0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, -0.5f,
        0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, 0.5f, 0.5f,
        -0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, 0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, -0.5f,
        -0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, -0.5f,
        -0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,
        0.5f, -0.5f, 0.5f
};

Cube::Cube(std::string &&name, const GLfloat *color_buffer): name{name} {
    init(color_buffer);
}

Cube::Cube(std::string &name, const GLfloat *color_buffer): name{name} {
    init(color_buffer);
}

void Cube::init(const GLfloat *color_buffer) {
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, getGLsizeiptr(sizeof(g_vertex_buffer)), g_vertex_buffer, GL_STATIC_DRAW);

    if (color_buffer != nullptr) {
        glGenBuffers(1, &this->color_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, this->color_buffer);
        glBufferData(GL_ARRAY_BUFFER, getGLsizeiptr(sizeof(g_vertex_buffer)), color_buffer, GL_STATIC_DRAW);
    }

    GL_ERROR();
}

Cube::~Cube() {
    if (vertex_buffer != 0) {
        glDeleteBuffers(1, &vertex_buffer);
        vertex_buffer = 0;
    }
    if (color_buffer != 0) {
        glDeleteBuffers(1, &vertex_buffer);
        color_buffer = 0;
    }
    if (VAO != 0) {
        glDeleteBuffers(1, &VAO);
        VAO = 0;
    }
}

void Cube::preDraw(Program &program) {
    GL_ERROR();

    glm::mat4 model = glm::mat4(0.5f);

    model = glm::scale(model, scale);
    model = glm::rotate(model, angle, rotate_axis);
    model = glm::translate(model, translation);

    program.setMat4(name, model);

    GL_ERROR();
}


void Cube::draw(Program &program) {
    GL_ERROR();

    glBindVertexArray(VAO);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glVertexAttribPointer(
            0,
            3,
            GL_FLOAT,
            GL_FALSE,
            0,
            0
    );
    if (color_buffer != 0) {
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
        glVertexAttribPointer(
                1,
                3,
                GL_FLOAT,
                GL_FALSE,
                0,
                0
        );
    }

    glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

    if (color_buffer != 0) {
        glDisableVertexAttribArray(1);
    }
    glDisableVertexAttribArray(0);

    GL_ERROR();
}

void Cube::postDraw(Program &program) {
    Drawable::postDraw(program);
}
