#ifndef OPENGLBOILERPLATE_MATERIAL_H
#define OPENGLBOILERPLATE_MATERIAL_H

#include <string>
#include <set>
#include "drawable.h"

namespace gl {
    class Material: public Drawable {
    public:
        std::string name;

        float diffuse;
        float specular;

        float shininess;

        void preDraw(Program &program) override;
    };
}

#endif //OPENGLBOILERPLATE_MATERIAL_H
