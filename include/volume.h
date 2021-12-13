#ifndef OPENGLBOILERPLATE_VOLUME_H
#define OPENGLBOILERPLATE_VOLUME_H

#include "voxels.h"
#include "volume-surface.h"

namespace gl {
    template<class T>
    class Volume: public Drawable {
    public:
        explicit Volume(std::string &name Voxels<T> &voxels);
        explicit Volume(std::string &name Voxels<T> &&voxels);
        explicit Volume(std::string &&name Voxels<T> &voxels);
        explicit Volume(std::string &&name Voxels<T> &&voxels);

        ~Volume() override;

        void draw(Program &program) override;

        std::string &name;

        glm::vec3 &translation;
        glm::vec3 &scale;

        float &angle;
        glm::vec3 &rotate_axis;

    private:
        Voxels<T> voxels;
        VolumeSurface surface;
    };
}

#endif //OPENGLBOILERPLATE_VOLUME_H
