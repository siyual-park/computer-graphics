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

namespace gl {
    namespace internal {
        WindowSize getWindowSizeFromViewport() {
            GLint viewport[4];
            glGetIntegerv(GL_VIEWPORT, viewport);

            auto width = viewport[2] - viewport[0];
            auto height = viewport[3] - viewport[1];

            return WindowSize{ .width = width, .height = height };
        }
    }
}

void cursorPosCallback(GLFWwindow *glfw_window, double x, double y) {
    gl::MousePositionEvent position{ .x = x, .y = y };

    auto window = findWindow(glfw_window);
    if (window != nullptr) {
        window->event_emitter.emit(position);
    }
}

void framebufferSizeCallback(GLFWwindow* glfw_window, int width, int height) {
    gl::WindowSize size{ .width = width, .height = height };

    auto window = findWindow(glfw_window);
    if (window != nullptr) {
        window->size.height = height;
        window->size.width = width;

        glViewport(0, 0, width, height);

        window->event_emitter.emit(size);
    }
}

void mouseButtonCallback(GLFWwindow* glfw_window, int button, int action, int mods) {
    auto window = findWindow(glfw_window);
    if (window != nullptr) {
        gl::MouseButtonEvent enter{ .button = button, .action = action };

        window->event_emitter.emit(enter);
    }
}

void scrollCallback(GLFWwindow* glfw_window, double x, double y) {
    gl::ScrollOffset offset{ .x = x, .y = y };

    auto window = findWindow(glfw_window);
    if (window != nullptr) {
        window->event_emitter.emit(offset);
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

    glViewport(0, 0, size.width, size.height);
}
void gl::Window::resize(gl::WindowSize &&size) {
    this->size = size;

    glViewport(0, 0, size.width, size.height);
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
    event_emitter.addListener(mouse_position_offset_event_provider);

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
    glfwSetScrollCallback(
            static_cast<GLFWwindow *>(context),
            scrollCallback
    );

    windows.insert(this);

    gl::initGLLoader();
}

void gl::Window::preDraw(gl::Program &program) {
    program.setVec2(
            "ScreenSize",
            glm::vec2((float)size.width,(float)size.height)
    );
}
