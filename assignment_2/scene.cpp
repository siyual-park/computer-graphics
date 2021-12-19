#include <glm/ext/matrix_transform.hpp>

#include "scene.h"
#include "camera.h"
#include "read-voxels.h"
#include "volume.h"
#include "light.h"
#include "material.h"

#include <GLFW/glfw3.h>

class Scene: public gl::Scene {
public:
    explicit Scene(gl::Renderer &renderer)
            : gl::Scene{renderer}
    {
        camera.zoom = 45.0f;
        volume.scale *= 0.001;

        light.name = "light";

        light.position = glm::vec3(5.0f, 5.0f, -5.0f);

        light.ambient = glm::vec3(1.0f, 1.0f, 1.0f);
        light.diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
        light.specular = glm::vec3(1.0f, 1.0f, 1.0f);

        light.constant = 1.0f;
        light.linear = 0.09f;
        light.quadratic = 0.032f;

        material.diffuse = 1;
        material.specular = 1;
        material.shininess = 1.0f;

        add(volume);
        add(light);
        add(camera);
        add(world);
    }

    glm::vec3 mapSphereCoordinate(gl::MousePositionEvent position) {
        int diameter = std::min(renderer.window.size.height, renderer.window.size.width);

        glm::vec3 coord{};

        coord[0] = static_cast<float>((2 * position.x - diameter) / diameter);
        coord[1] = static_cast<float>(-1.0 * (2 * position.y - diameter) / diameter);

        float length_squared = coord[0] * coord[0] + coord[1] * coord[1];

        if (length_squared <= 1.0) {
            coord[2] = std::sqrt(1.0f - length_squared);
        } else {
            coord = glm::normalize(coord);
        }

        return coord;
    }

    float angleBetween(glm::vec3 a, glm::vec3 b) {
        glm::vec3 origin = glm::zero<glm::vec3>();

        glm::vec3 da = glm::normalize(a - origin);
        glm::vec3 db = glm::normalize(b - origin);

        return glm::acos(glm::dot(da, db));
    }

    void onMouseCursorChange(gl::MousePositionEvent position) override {

    }

    void onMouseCursorChange(gl::MousePositionOffsetEvent offset) override {
        if (!is_mouse_enter) {
            return;
        }

        const auto normalize_x = static_cast<float>(offset.x / renderer.window.size.width);
        const auto normalize_y = static_cast<float>(offset.y / renderer.window.size.height);

        if (enter_button == GLFW_MOUSE_BUTTON_1) {
            camera.position += glm::vec3(normalize_x, normalize_y, 0.0f);
        } else if (enter_button == GLFW_MOUSE_BUTTON_2) {
            glm::vec3 arc_start_point = mapSphereCoordinate(offset.start);
            glm::vec3 arc_end_point = mapSphereCoordinate(offset.end);

            if (arc_start_point == arc_end_point) {
                return;
            }

            glm::vec3 rotate_axis = glm::cross(arc_start_point, arc_end_point);
            float angle = angleBetween(arc_start_point, arc_end_point);

            auto rotate_axis_distance = glm::distance(rotate_axis, glm::zero<glm::vec3>());
            if (
                    angle == NAN || angle == 0 || angle == INFINITY ||
                    rotate_axis_distance == NAN || rotate_axis_distance <= 0.01 || rotate_axis_distance == INFINITY
                    ) {
                return;
            }

            world.translation = glm::rotate(world.translation, angle, rotate_axis);
        }
    }

    void onScroll(gl::ScrollOffset offset) override {
        const auto normalize_y = static_cast<float>(offset.y / renderer.window.size.height);

        if (normalize_y + glm::distance(glm::zero<glm::vec3>(), camera.scale) < 0.5) {
            return;
        }
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

    gl::World world{};
    gl::Camera camera{glm::vec3(0.0f, 0.0f, 3.0f)};

    gl::Volume<signed short> volume{
        std::move(std::string{"model"}),
        gl::readVoxels<signed short>("./resources/objects/volume", gl::ENDIAN_TYPE::BIG),
        this
    };

    gl::Light light{};
    gl::Material material{};
};
