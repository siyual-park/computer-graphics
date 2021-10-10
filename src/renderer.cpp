#include "renderer.h"

#include <chrono>

gl::Renderer::Renderer(Window &window)
        : window{window} {
}

gl::Renderer::~Renderer() = default;

void gl::Renderer::run() {
    auto last_frame_time = std::chrono::system_clock::now();
    do {
        auto now = std::chrono::system_clock::now();

        std::chrono::duration<double> delta_time = now - last_frame_time;

        render(delta_time.count());
        window.update();

        last_frame_time = now;

    } while (window.isClose());
}

void gl::Renderer::render(double) {

}