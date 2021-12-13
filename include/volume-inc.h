#ifndef OPENGLBOILERPLATE_VOLUME_INC_H
#define OPENGLBOILERPLATE_VOLUME_INC_H

#include "volume.h"

template<class T>
gl::Volume<T>::Volume(std::string &name, Voxels<T> &voxels)
        : voxels{voxels},
          surface{name},
          frame_buffer{},
          frame_buffer_texture{}
{
    init();
}

template<class T>
gl::Volume<T>::Volume(std::string &name, gl::Voxels<T> &&voxels)
        : voxels{voxels},
          surface{name},
          frame_buffer{},
          frame_buffer_texture{}
{
    init();
}

template<class T>
gl::Volume<T>::Volume(std::string &&name, gl::Voxels<T> &voxels)
        : voxels{voxels},
          surface{name},
          frame_buffer{},
          frame_buffer_texture{}
{
    init();
}

template<class T>
gl::Volume<T>::Volume(std::string &&name, gl::Voxels<T> &&voxels)
        : voxels{voxels},
          surface{name},
          frame_buffer{},
          frame_buffer_texture{}
{
    init();
}

template<class T>
void gl::Volume<T>::init() {
    backface_vertex_shader.compile();
    backface_fragment_shader.compile();

    raycasting_vertex_shader.compile();
    raycasting_fragment_shader.compile();

    frame_buffer.attach(frame_buffer_texture);

    surface.scale = glm::vec3(
            voxels.size.width * voxels.spacing.x,
            voxels.size.height * voxels.spacing.y,
            voxels.size.depth * voxels.spacing.z
    );
}

template<class T>
gl::Volume<T>::~Volume() = default;

template<class T>
void gl::Volume<T>::draw(gl::Program &program) {
    frame_buffer.bind();

    program.detachAllShader();
    program.attach(backface_fragment_shader);
    program.attach(backface_vertex_shader);
    program.link();

    program.use();
    draw_surface(program, GL_FRONT);
    program.disuse();

    frame_buffer.unbind();

    program.detachAllShader();
    program.attach(raycasting_fragment_shader);
    program.attach(raycasting_vertex_shader);
    program.link();

    program.use();

    program.setFloat("StepSize", 0.001f);
    auto exit_points = program.getLocation("ExitPoints");
    if (exit_points >= 0) {
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, frame_buffer_texture.id);
        glUniform1i(exit_points, 1);
    }
    auto volume_tex = program.getLocation("VolumeTex");
    if (volume_tex >= 0) {
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_3D, frame_buffer_texture.id);
        glUniform1i(volume_tex, 1);
    }

    draw_surface(program, GL_BACK);

    program.disuse();
}

template<class T>
void gl::Volume<T>::draw_surface(gl::Program &program, int mode) {
    glEnable(GL_CULL_FACE);
    glCullFace(mode);

    surface.draw(program);

    glDisable(GL_CULL_FACE);
}


#endif //OPENGLBOILERPLATE_VOLUME_INC_H
