#include "material.h"

void gl::Material::preDraw(Program &program) {
    program.setFloat(name + ".shininess", shininess);
    program.setFloat(name + ".diffuse", diffuse);
    program.setFloat(name + ".specular", specular);
}
