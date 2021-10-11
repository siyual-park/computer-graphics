#include "window.h"

#include <set>
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include "initializer.h"
#include "error.h"

std::set<gl::Window*> windows{};

gl::Window* findWindow(GLFWwindow *glfw_window) {
    for (auto &window: windows) {
        if (window->context == glfw_window) {
            return window;
        }
    }

    return nullptr;
}


void cursorPosCallback(GLFWwindow *glfw_window, double x, double y) {
    gl::MousePosition position{ .x = x, .y = y };

    auto window = findWindow(glfw_window);
    if (window != nullptr) {
        for (auto callback: window->mouse_position_control.callbacks) {
            callback->run(position);
        }
    }
}

void framebufferSizeCallback(GLFWwindow* glfw_window, int width, int height) {
    gl::WindowSize size{ .width = width, .height = height };

    auto window = findWindow(glfw_window);
    if (window != nullptr) {
        window->size.height = height;
        window->size.width = width;

        glViewport(0, 0, width, height);

        for (auto callback: window->window_size_control.callbacks) {
            callback->run(size);
        }
    }
}

void mouseButtonCallback(GLFWwindow* glfw_window, int button, int action, int mods) {
    auto window = findWindow(glfw_window);
    if (window != nullptr) {
        gl::MouseButtonEvent enter{ .button = button, .action = action };

        for (auto callback: window->mouse_button_control.callbacks) {
            callback->run(enter);
        }
    }
}


gl::Window::Window(std::string& title, WindowSize &size): title{title}, size{size} {
    this->title = title;

    init();
}
gl::Window::Window(std::string&& title, WindowSize &size): title{title}, size{size} {
    this->title = title;

    init();
}
gl::Window::Window(std::string& title, WindowSize &&size): title{title}, size{size} {
    this->title = title;

    init();
}
gl::Window::Window(std::string&& title, WindowSize &&size): title{title}, size{size} {
    this->title = title;

    init();
}

gl::Window::~Window() {
    glfwDestroyWindow(static_cast<GLFWwindow *>(context));
    windows.erase(this);
}

gl::WindowSize gl::Window::getSize() const noexcept {
    return size;
}
void gl::Window::resize(gl::WindowSize &size) {
    this->size = size;
}
void gl::Window::resize(gl::WindowSize &&size) {
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
    gl::initWindowSystem();

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
    glfwSetFramebufferSizeCallback(
            static_cast<GLFWwindow *>(context),
            framebufferSizeCallback
    );
    glfwSetMouseButtonCallback(
            static_cast<GLFWwindow *>(context),
            mouseButtonCallback
    );

    windows.insert(this);

    gl::initGLLoader();
}
