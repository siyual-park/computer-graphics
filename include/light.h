#ifndef OPENGLBOILERPLATE_LIGHT_H
#define OPENGLBOILERPLATE_LIGHT_H

#include <string>
#include <set>
#include "drawable.h"

namespace gl {
    struct Light: public Drawable {
        std::string name;

        glm::vec3 position;

        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;

        float constant;
        float linear;
        float quadratic;

        void preDraw(Program &program) override;
    };
}

#endif //OPENGLBOILERPLATE_LIGHT_H
