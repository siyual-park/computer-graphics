#include "light.h"

void gl::Light::preDraw(gl::Program &program) {
    program.setVec3(name + ".position", position);
    program.setVec3(name + ".ambient", ambient);
    program.setVec3(name + ".diffuse", diffuse);
    program.setVec3(name + ".specular", specular);

    program.setFloat(name + ".constant", constant);
    program.setFloat(name + ".linear", linear);
    program.setFloat(name + ".quadratic", quadratic);
}