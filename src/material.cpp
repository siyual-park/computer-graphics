#include "material.h"

void gl::Material::preDraw(Program &program) {
    program.setFloat(name + ".shininess", 32.0f);

    if (loaded.find(&program) == loaded.end()) {
        program.setInt(name + ".diffuse", 0);
        program.setInt(name + ".specular", 1);

        loaded.insert(&program);
    }
}
