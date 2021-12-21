#include "volume-surface.h"

using namespace gl;

VolumeSurface::VolumeSurface(std::string &name): Cube{name} {

}

VolumeSurface::VolumeSurface(std::string &&name): Cube{name} {

}

VolumeSurface::~VolumeSurface() = default;

void VolumeSurface::draw(Program &program) {
    Cube::draw(program);
}
