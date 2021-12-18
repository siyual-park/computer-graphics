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
        explicit Volume(std::string &name, Voxels<T> &voxels, Drawable *parent = nullptr);
        explicit Volume(std::string &&name, Voxels<T> &voxels, Drawable *parent = nullptr);
        explicit Volume(std::string &name, Voxels<T> &&voxels, Drawable *parent = nullptr);
        explicit Volume(std::string &&name, Voxels<T> &&voxels, Drawable *parent = nullptr);

        ~Volume() override;

        void preDraw(Program &program) override;
        void draw(Program &program) override;
        void postDraw(Program &program) override;

        std::string &name = surface.name;

        glm::vec3 &translation = surface.translation;
        glm::vec3 &scale = surface.scale;

        float &angle = surface.angle;
        glm::vec3 &rotate_axis = surface.rotate_axis;

    private:
        void init();

        Voxels<T> voxels;
        VolumeSurface surface;
        Drawable *parent;

        gl::Texture3d<T> voxel_texture{
                voxels.data,
                Texture3dSize{.x = (int) voxels.size.width, .y = (int) voxels.size.height, .z = (int) voxels.size.depth},
                getRedType<T>(),
                getRedFormat<T>()
        };

        gl::FrameBuffer frame_buffer{};

        gl::VertexShader backface_vertex_shader{"./shaders/backface.vert.glsl"};
        gl::FragmentShader backface_fragment_shader{"./shaders/backface.frag.glsl"};

        gl::VertexShader ray_casting_vertex_shader{"./shaders/raycasting.vert.glsl"};
        gl::FragmentShader ray_casting_fragment_shader{"./shaders/raycasting.frag.glsl"};

        int cull_face{GL_FRONT};
    };
}

#include "volume-inc.h"

#endif //OPENGLBOILERPLATE_VOLUME_H
