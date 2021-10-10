#include "renderer.h"

#include <chrono>

gl::Renderer::Renderer(Window &window)
        : window{window}, fps{0} {
}

gl::Renderer::~Renderer() = default;

void gl::Renderer::run() {
    auto start_time = std::chrono::system_clock::now();
    auto frame_start_time = std::chrono::system_clock::now();
    
    std::chrono::duration<double> current_time{};
    std::chrono::duration<double> frame_current_time{};

    unsigned int fps = 0;
    do {
        auto now = std::chrono::system_clock::now();

        current_time = now - start_time;
        frame_current_time = now - frame_start_time;

        fps++;
        if (frame_current_time.count() >= 1.0) {
            this->fps = fps;
            frame_start_time = now;
            fps = 0;
        }

        render(current_time.count());
        window.update();

    } while (window.isClose());
}

void gl::Renderer::render(double) {

}