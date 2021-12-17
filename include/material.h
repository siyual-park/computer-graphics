#ifndef OPENGLBOILERPLATE_MATERIAL_H
#define OPENGLBOILERPLATE_MATERIAL_H

#include <string>
#include <set>
#include "drawable.h"

namespace gl {
    class Material: public Drawable {
    public:
        std::string name;

        int diffuse;
        int specular;

        float shininess;

        void preDraw(Program &program) override;

    private:
        std::set<Program*> loaded{};
    };
}

#endif //OPENGLBOILERPLATE_MATERIAL_H
