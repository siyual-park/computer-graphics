#include "world.h"

#include "program.h"

void gl::World::preDraw(gl::Program &program) {
    program.setMat4("world", translation);
}

void gl::World::draw(gl::Program &program) {
    program.setMat4("world", translation);
}

void gl::World::postDraw(gl::Program &program) {
    Drawable::postDraw(program);
}
