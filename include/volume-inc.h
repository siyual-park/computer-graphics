#ifndef OPENGLBOILERPLATE_VOLUME_INC_H
#define OPENGLBOILERPLATE_VOLUME_INC_H

#include "volume.h"

#include <limits>

template<class T>
gl::Volume<T>::Volume(std::string &name, Voxels<T> &voxels, Drawable *parent)
        : voxels{voxels},
          surface{name},
          parent{parent}
{
    init();
}

template<class T>
gl::Volume<T>::Volume(std::string &&name, gl::Voxels<T> &voxels, Drawable *parent)
        : voxels{voxels},
          surface{name},
          parent{parent}
{
    init();
}

template<class T>
gl::Volume<T>::Volume(std::string &name, Voxels<T> &&voxels, Drawable *parent)
        : voxels{voxels},
          surface{name},
          parent{parent}
{
    init();
}

template<class T>
gl::Volume<T>::Volume(std::string &&name, gl::Voxels<T> &&voxels, Drawable *parent)
        : voxels{voxels},
          surface{name},
          parent{parent}
{
    init();
}

template<class T>
void gl::Volume<T>::init() {
    backface_vertex_shader.compile();
    backface_fragment_shader.compile();

    ray_casting_vertex_shader.compile();
    ray_casting_fragment_shader.compile();

    surface.scale = glm::vec3(
            voxels.size.width * voxels.spacing.x,
            voxels.size.height * voxels.spacing.y,
            voxels.size.depth * voxels.spacing.z
    );
}

template<class T>
gl::Volume<T>::~Volume() = default;

template<class T>
void gl::Volume<T>::preDraw(gl::Program &program) {
    GL_ERROR();

    glEnable(GL_DEPTH_TEST);

    if (cull_face == GL_FRONT) {
        frame_buffer.texture.bind();
        voxel_texture.bind();

        frame_buffer.bind();

        program.detaches(2);
        program.attach(backface_vertex_shader);
        program.attach(backface_fragment_shader);
        program.link();

        program.use();
    } else {
        program.detaches(2);
        program.attach(ray_casting_vertex_shader);
        program.attach(ray_casting_fragment_shader);
        program.link();

        program.use();

        auto exit_points = program.getLocation("ExitPoints");
        if (exit_points >= 0) {
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, frame_buffer.texture.id);
            glUniform1i(exit_points, 1);
        }
        auto volume_tex = program.getLocation("VolumeTex");
        if (volume_tex >= 0) {
            glActiveTexture(GL_TEXTURE2);
            glBindTexture(GL_TEXTURE_3D, voxel_texture.id);
            glUniform1i(volume_tex, 2);
        }

        program.setVec3(
                "VolumeSize",
                glm::vec3(voxels.size.width, voxels.size.height, voxels.size.depth)
        );
    }

    GL_ERROR();

    surface.preDraw(program);
}

template<class T>
void gl::Volume<T>::draw(gl::Program &program) {
    GL_ERROR();

    glEnable(GL_CULL_FACE);

    glCullFace(cull_face);

    if (cull_face == GL_FRONT) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    surface.draw(program);

    glDisable(GL_CULL_FACE);

    GL_ERROR();
}

template<class T>
void gl::Volume<T>::postDraw(gl::Program &program) {
    GL_ERROR();

    surface.postDraw(program);

    if (cull_face == GL_FRONT) {
        cull_face = GL_BACK;

        program.disuse();
        frame_buffer.unbind();

        if (parent != nullptr) {
            parent->draw(program);
        }
    } else {
        cull_face = GL_FRONT;

        glActiveTexture(GL_TEXTURE1);
        frame_buffer.texture.unbind();
        glActiveTexture(GL_TEXTURE2);
        voxel_texture.unbind();

        glActiveTexture(GL_TEXTURE0);

        program.disuse();
    }

    GL_ERROR();
}

#endif //OPENGLBOILERPLATE_VOLUME_INC_H
