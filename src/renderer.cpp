#include "renderer.h"

#include <chrono>
#include "error.h"

gl::Renderer::Renderer(Window &window)
        : window{window} {
}

gl::Renderer::~Renderer() = default;

void gl::Renderer::run() {
    auto last_frame_time = std::chrono::system_clock::now();
    do {
        auto now = std::chrono::system_clock::now();

        std::chrono::duration<double> delta_time = now - last_frame_time;

        GL_ERROR();

        render(delta_time.count());
        window.update();

        last_frame_time = now;

        GL_ERROR();
    } while (window.isClose());
}

void gl::Renderer::render(double) {

}