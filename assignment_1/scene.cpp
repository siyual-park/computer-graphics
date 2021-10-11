#include <glm/ext/matrix_transform.hpp>

#include "scene.h"
#include "camera.h"
#include "model.h"
#include "light.h"
#include "material.h"

#include <GLFW/glfw3.h>

class Scene: public gl::Scene {
public:
    explicit Scene(gl::Renderer &renderer, gl::Camera &camera, gl::Model &model): gl::Scene{renderer, camera}, model{model} {
        light.name = "light";

        light.position = glm::vec3(1.2f, 1.0f, 2.0f);

        light.ambient = glm::vec3(0.2f, 0.2f, 0.2f);
        light.diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
        light.specular = glm::vec3(1.0f, 1.0f, 1.0f);

        light.constant = 1.0f;
        light.linear = 0.09f;
        light.quadratic = 0.032f;

        material.name = "material";

        material.diffuse = 0;
        material.specular = 1;
        material.shininess = 1;

        add(model);
        add(light);
        add(material);
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
            world.mat = glm::rotate(world.mat, glm::radians(normalize_x * 90), glm::vec3(0, 1.0, 0));
            world.mat = glm::rotate(world.mat, glm::radians(normalize_y * 90), glm::vec3(1.0, 0, 0));
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
    gl::Light light{};
    gl::Material material{};
};
