#include "camera.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

#include "window.h"

gl::Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch): front{glm::vec3(0.0f, 0.0f, -1.0f)}, zoom{ZOOM} {
    this->position = position;
    this->world_up = up;
    this->yaw = yaw;
    this->pitch = pitch;

    update();
}

glm::mat4 gl::Camera::getViewMatrix() const {
    auto mat = glm::lookAt(position, position + front, up);
    mat = glm::scale(mat, scale);

    return mat;
}

void gl::Camera::preDraw(gl::Program &program) {
    auto window_size = gl::internal::getWindowSizeFromViewport();

    update();

    glm::mat4 projection = glm::perspective(
            glm::radians(zoom),
            static_cast<float>(window_size.width) / static_cast<float>(window_size.height),
            0.1f,
            1000.0f
    );
    glm::mat4 view = getViewMatrix();

    program.setMat4("projection", projection);
    program.setMat4("view", view);
    program.setVec3("viewPos", position);
}

void gl::Camera::update() {
    glm::vec3 new_front{
            cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
            sin(glm::radians(pitch)),
            sin(glm::radians(yaw)) * cos(glm::radians(pitch))
    };

    front = glm::normalize(new_front);
    right = glm::normalize(glm::cross(front, world_up));
    up = glm::normalize(glm::cross(right, front));
}
