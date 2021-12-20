#ifndef OPENGLBOILERPLATE_VOXELS_H
#define OPENGLBOILERPLATE_VOXELS_H

#include <string>

#include "drawable.h"
#include "gl-object.h"
#include "transfer-function.h"

namespace gl {
    struct Size {
        std::size_t width;
        std::size_t height;
        std::size_t depth;
    };

    struct Spacing {
        float x;
        float y;
        float z;
    };

    template<class T>
    class Voxels {
    public:
        explicit Voxels(Size size, TransferFunction &transfer_function, Spacing spacing = {1.0f, 1.0f, 1.0f});
        explicit Voxels(Size size, TransferFunction &&transfer_function, Spacing spacing = {1.0f, 1.0f, 1.0f});
        Voxels(Voxels<T> &other) noexcept;
        Voxels(Voxels<T> &&other) noexcept;
        ~Voxels();

        T* data;

        TransferFunction transfer_function;
        Size size;
        Spacing spacing;
    };
}

#include "voxels-inc.h"

#endif //OPENGLBOILERPLATE_VOXELS_H
