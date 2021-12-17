#ifndef OPENGLBOILERPLATE_VOLUME_H
#define OPENGLBOILERPLATE_VOLUME_H

#include "voxels.h"
#include "volume-surface.h"
#include "frame-buffer.h"
#include "texture2d.h"
#include "texture3d.h"

namespace gl {
    namespace internal {
        int mappingTypeToRed(int type);
    }

    template<class T>
    class Volume: public Drawable {
    public:
        explicit Volume(std::string &name, Voxels<T> &voxels);
        explicit Volume(std::string &name, Voxels<T> &&voxels);
        explicit Volume(std::string &&name, Voxels<T> &voxels);
        explicit Volume(std::string &&name, Voxels<T> &&voxels);

        ~Volume() override;

        void draw(Program &program) override;

        std::string &name = surface.name;

        glm::vec3 &translation = surface.translation;
        glm::vec3 &scale = surface.scale;

        float &angle = surface.angle;
        glm::vec3 &rotate_axis = surface.rotate_axis;

    private:
        void init();

        void draw_surface(Program &program, int mode);

        Voxels<T> voxels;
        VolumeSurface surface;

//        gl::Texture2d<float> frame_buffer_texture{nullptr, internal::getTexture2dSizeFromViewport(), GL_RGBA16F, GL_RGBA};
//        gl::Texture3d<T> voxel_texture{
//                voxels.data,
//                Texture3dSize{.x = (int) voxels.size.width, .y = (int) voxels.size.height, .z = (int) voxels.size.depth},
//                getRedType<T>(),
//                GL_RED_INTEGER
//        };
//
//        gl::FrameBuffer frame_buffer{&frame_buffer_texture};

        gl::VertexShader backface_vertex_shader{"./shaders/backface.vert.glsl"};
        gl::FragmentShader backface_fragment_shader{"./shaders/backface.frag.glsl"};

        gl::VertexShader raycasting_vertex_shader{"./shaders/raycasting.vert.glsl"};
        gl::FragmentShader raycasting_fragment_shader{"./shaders/raycasting.frag.glsl"};
    };
}

#include "volume-inc.h"

#endif //OPENGLBOILERPLATE_VOLUME_H
