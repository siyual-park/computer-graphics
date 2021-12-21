#include "cube.h"

#include <glm/ext/matrix_transform.hpp>

using namespace gl;

const GLfloat g_vertices[] = {
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f
};

const GLuint g_indices[] = {
        1, 5, 7,
        7, 3, 1,
        0, 2, 6,
        6, 4, 0,
        0, 1, 3,
        3, 2, 0,
        7, 5, 4,
        4, 6, 7,
        2, 3, 7,
        7, 6, 2,
        1, 0, 4,
        4, 5, 1
};

Cube::Cube(std::string &&name): name{name} {
    init();
}

Cube::Cube(std::string &name): name{name} {
    init();
}

void Cube::init() {
    GL_ERROR();

    glGenBuffers(2, gbo);

    GLuint vertexdat = gbo[0];
    GLuint veridxdat = gbo[1];

    glBindBuffer(GL_ARRAY_BUFFER, vertexdat);
    glBufferData(GL_ARRAY_BUFFER, getGLsizeiptr(sizeof(g_vertices)), g_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, veridxdat);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, getGLsizeiptr(sizeof(g_indices)), g_indices, GL_STATIC_DRAW);

    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, vertexdat);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, veridxdat);

    GL_ERROR();
}

Cube::~Cube() {
    if (gbo[0] != 0 && gbo[1] != 0) {
        glDeleteBuffers(2, gbo);
        gbo[0] = 0;
        gbo[1] = 0;
    }
    if (vao != 0) {
        glDeleteBuffers(1, &vao);
        vao = 0;
    }
}

void Cube::preDraw(Program &program) {
    GL_ERROR();

    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, glm::vec3(-0.5f, -0.5f, -0.5f));
    model = glm::scale(model, scale);
    model = glm::rotate(model, angle, rotate_axis);
    model = glm::translate(model, translation);

    program.setMat4(name, model);

    GL_ERROR();
}


void Cube::draw(Program &program) {
    GL_ERROR();

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);

    GL_ERROR();
}

void Cube::postDraw(Program &program) {
    Drawable::postDraw(program);
}
