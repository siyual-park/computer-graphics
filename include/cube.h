#ifndef OPENGLBOILERPLATE_CUBE_H
#define OPENGLBOILERPLATE_CUBE_H

#include "drawable.h"

namespace gl {
    class Cube: public Drawable {
    public:
        explicit Cube(std::string &name, const GLfloat *color_buffer = nullptr);
        explicit Cube(std::string &&name, const GLfloat *color_buffer = nullptr);
        virtual ~Cube();

        void draw(Program &program) override;

        std::string name;

        glm::vec3 translation = glm::vec3(0.0, 0.0, 0.0);
        glm::vec3 scale = glm::vec3(1.0, 1.0, 1.0);

        float angle = glm::radians(0.0f);
        glm::vec3 rotate_axis = glm::vec3(1.0f, 1.0f, 1.0f);
    protected:
        void init(const GLfloat *color_buffer);

        unsigned int VAO;
        unsigned int vertex_buffer;
        unsigned int color_buffer;
    };
}

#endif //OPENGLBOILERPLATE_CUBE_H
