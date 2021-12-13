#include "gl-object.h"

#include "initializer.h"

gl::GLObject::GLObject()
        : id{} {
    initGLLoader();
}