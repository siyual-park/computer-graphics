#ifndef OPENGLBOILERPLATE_INITIALIZER_H
#define OPENGLBOILERPLATE_INITIALIZER_H

namespace gl {
    struct Version {
        int major;
        int minor;
    };


    extern Version version;

    void setVersion(Version new_version);
    void initWindowSystem();
    void initGLLoader();

    extern bool inited_window_system;
    extern bool inited_gl_loader;
}

#endif //OPENGLBOILERPLATE_INITIALIZER_H
