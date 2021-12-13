#ifndef OPENGLBOILERPLATE_VOLUME_SURFACE_H
#define OPENGLBOILERPLATE_VOLUME_SURFACE_H

#include "cube.h"

namespace gl {
    class VolumeSurface: public Cube {
    public:
        explicit VolumeSurface(std::string &name);
        explicit VolumeSurface(std::string &&name);
        ~VolumeSurface() override;

        void draw(Program &program) override;
    };
}

#endif //OPENGLBOILERPLATE_VOLUME_SURFACE_H
