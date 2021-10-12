#include "world.h"

#include "program.h"

void gl::World::draw(gl::Program &program) {
    program.setMat4("world", translation);
}
