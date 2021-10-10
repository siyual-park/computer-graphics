#include <glm/ext/matrix_transform.hpp>
#include "camera.h"

gl::Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch): front{glm::vec3(0.0f, 0.0f, -1.0f)}, movement_speed{SPEED}, mouse_sensitivity{SENSITIVITY}, zoom{ZOOM} {
    this->position = position;
    this->world_up = up;
    this->yaw = yaw;
    this->pitch = pitch;

    update();
}

glm::mat4 gl::Camera::getViewMatrix() const {
    return glm::lookAt(position, position + front, up);
}

void gl::Camera::update() {
    glm::vec3 front{};

    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    this->front = glm::normalize(front);
    this->right = glm::normalize(glm::cross(this->front, this->world_up));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    this->up = glm::normalize(glm::cross(this->right, this->front));
}
