#include "initializer.h"
#include "window.h"
#include "volume-reader.h"

#include "./renderer.cpp"


int main() {
    gl::setVersion(gl::Version{ .major = 3, .minor =  3 });

    gl::Window window{"Assignment 2", { .width = 1024, .height = 768 }};

    gl::Camera camera{glm::vec3(0.0f, 0.0f, 3.0f)};

    camera.zoom = 45.0f;

    gl::VolumeReader<signed short> reader{"./resources/objects/sample/volume.raw", gl::ENDIAN_TYPE::BIG};
    // TODO (change to read metadata from file)
    auto volume{std::move(reader.read(gl::Size{256, 256, 39}, gl::Spacing{1.4532, 1.4532, 4}))};

    Renderer renderer{window, camera};

    renderer.run();

    return 0;
}