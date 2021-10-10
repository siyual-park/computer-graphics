#include "base-object.h"

#include "initializer.h"

gl::BaseObject::BaseObject()
        : id{} {
    initGLLoader();
}