#include "window.h"

#include <set>
#include <GLFW/glfw3.h>
#include "error.h"

std::set<gl::Window*> windows{};

void cursorPosCallback(GLFWwindow *window, double x, double y) {
    gl::Position position{ .x = x, .y = y };

    std::for_each(windows.begin(), windows.end(), [&position](gl::Window *window) {
        if (window->context == window) {
            std::for_each(window->mouse_control.callbacks.begin(), window->mouse_control.callbacks.end(), [&position](gl::MouseCallback *callback) {
                callback->run(position);
            });
        }
    });
}

gl::Window::Window(std::string& title, Size &size): size{}, context{}, mouse_control{} {
    this->title = title;
    this->size = size;

    init();
}
gl::Window::Window(std::string&& title, Size &size): size{}, context{}, mouse_control{} {
    this->title = title;
    this->size = size;

    init();
}
gl::Window::Window(std::string& title, Size &&size): size{}, context{}, mouse_control{} {
    this->title = title;
    this->size = size;

    init();
}
gl::Window::Window(std::string&& title, Size &&size): size{}, context{}, mouse_control{} {
    this->title = title;
    this->size = size;

    init();
}

gl::Window::~Window() {
    glfwDestroyWindow(static_cast<GLFWwindow *>(context));
    windows.erase(this);
}

gl::Size gl::Window::getSize() const noexcept {
    return size;
}
void gl::Window::resize(gl::Size &size) {
    this->size = size;
}
void gl::Window::resize(gl::Size &&size) {
    this->size = size;
}

void gl::Window::update() {
    // 버퍼들을 교체
    glfwSwapBuffers(static_cast<GLFWwindow *>(context));
    glfwPollEvents();
}

bool gl::Window::isClose() {
    return glfwGetKey(static_cast<GLFWwindow *>(context), GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(static_cast<GLFWwindow *>(context)) == 0;
}

void gl::Window::init() {
    context = glfwCreateWindow(size.width, size.height, title.c_str(), nullptr, nullptr);
    if (context == nullptr) {
        errorHandle(Error::GLFW, "Failed to open GLFW window.");
        return;
    }
    glfwMakeContextCurrent(static_cast<GLFWwindow *>(context));

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(static_cast<GLFWwindow *>(context), GLFW_STICKY_KEYS, GL_TRUE);

    glfwSetCursorPosCallback(
            static_cast<GLFWwindow *>(context),
            static_cast<GLFWcursorposfun>(cursorPosCallback)
    );

    windows.insert(this);
}

