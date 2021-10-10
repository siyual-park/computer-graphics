#include "renderer.h"

#include <chrono>

gl::Renderer::Renderer(Window &window)
        : window{window} {
}

gl::Renderer::~Renderer() = default;

void gl::Renderer::run() {
    auto start_time = std::chrono::system_clock::now();
    auto frame_start_time = std::chrono::system_clock::now();
    
    std::chrono::duration<double> current_time{};
    std::chrono::duration<double> frame_current_time{};

    unsigned int frame = 0;
    double fps = 0;

    do {
        auto now = std::chrono::system_clock::now();

        current_time = now - start_time;
        frame_current_time = now - frame_start_time;

        frame++;
        if (frame_current_time.count() >= 1.0) {
            fps = 1000.0 / static_cast<double>(frame);
            frame_start_time = now;
            frame = 0;
        }

        render(current_time.count());
        window.update();

    } while (window.isClose());
}

void gl::Renderer::render(double) {

}