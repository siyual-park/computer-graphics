#include "base-object.h"

#include "initializer.h"
#include "error.h"

gl::BaseObject::BaseObject()
        : name{} {
    initGLLoader();
}

unsigned int gl::BaseObject::getName() const {
    if (!name) {
        errorHandle(Error::GL, "This name is not generated.");
        return 0;
    }

    return name;
}