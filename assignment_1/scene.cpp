#include <glm/ext/matrix_transform.hpp>

#include "scene.h"
#include "camera.h"
#include "model.h"

#include <GLFW/glfw3.h>

class Scene: public gl::Scene {
public:
    explicit Scene(gl::Renderer &renderer, gl::Camera &camera, gl::Model &model): gl::Scene{renderer, camera}, model{model} {
        add(model);
    }

    void onMouseCursorChange(gl::MousePosition position) override {

    }

    void onMouseCursorChange(gl::MousePositionOffset offset) override {
        if (!is_mouse_enter) {
            return;
        }

        const auto normalize_x = static_cast<float>(offset.x / renderer.window.size.width);
        const auto normalize_y = static_cast<float>(offset.y / renderer.window.size.height);

        if (enter_button == GLFW_MOUSE_BUTTON_1) {
            camera.position += glm::vec3(normalize_x, normalize_y, 0.0f);
        } else if (enter_button == GLFW_MOUSE_BUTTON_2) {
            camera.yaw += normalize_x * 90;
            camera.pitch += normalize_y * 90;

            if (camera.pitch > 89.0f)
                camera.pitch =  89.0f;
            if (camera.pitch < -89.0f)
                camera.pitch = -89.0f;
        }
    }

    void onScroll(gl::ScrollOffset offset) override {
        const auto normalize_y = static_cast<float>(offset.y / renderer.window.size.height);

        camera.scale += normalize_y;
    };

    void onMouseEnter(int button) override {
        is_mouse_enter = true;
        enter_button = button;
    };
    void onMouseRelease(int button) override {
        is_mouse_enter = false;
    };


private:
    bool is_mouse_enter{false};
    int enter_button{0};

    gl::Model &model;
};
