#ifndef OPENGLBOILERPLATE_CAMERA_H
#define OPENGLBOILERPLATE_CAMERA_H

#include <glm/glm.hpp>

namespace gl {
    const float YAW         = -90.0f;
    const float PITCH       =  0.0f;
    const float ZOOM        =  45.0f;

    enum CameraMovement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };

    class Camera {
    public:
        explicit Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);

        glm::mat4 getViewMatrix() const;

        void update();

        glm::vec3 position{};
        glm::vec3 front;
        glm::vec3 up{};
        glm::vec3 right{};
        glm::vec3 world_up{};

        float yaw;
        float pitch;

        float zoom;
    };
}

#endif //OPENGLBOILERPLATE_CAMERA_H
