#ifndef OPENGLBOILERPLATE_CUBE_H
#define OPENGLBOILERPLATE_CUBE_H

#include "drawable.h"

namespace gl {
    class Cube: public Drawable {
    public:
        explicit Cube(std::string &name);
        explicit Cube(std::string &&name);
        virtual ~Cube();

        void preDraw(Program &program) override;
        void draw(Program &program) override;
        void postDraw(Program &program) override;

        std::string name;

        glm::vec3 translation = glm::vec3(0.0, 0.0, 0.0);
        glm::vec3 scale = glm::vec3(1.0, 1.0, 1.0);

        float angle = glm::radians(0.0f);
        glm::vec3 rotate_axis = glm::vec3(1.0f, 1.0f, 1.0f);

    protected:
        unsigned int gbo[2]{};
        unsigned int vao{};

    private:
        void init();
    };
}

#endif //OPENGLBOILERPLATE_CUBE_H
