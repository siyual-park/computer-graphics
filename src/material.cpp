#include "material.h"

void gl::Material::preDraw(Program &program) {
    program.setFloat(name + ".shininess", shininess);

    if (loaded.find(&program) == loaded.end()) {
        program.setInt(name + ".diffuse", diffuse);
        program.setInt(name + ".specular", specular);

        loaded.insert(&program);
    }
}
