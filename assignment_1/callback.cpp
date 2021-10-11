#include <iostream>

#include "callback.h"
#include "camera.h"
#include "mouse.h"
#include "model.h"

class PositionChangeCallback: public gl::Callback<gl::MousePosition> {
public:
    explicit PositionChangeCallback(gl::Camera &camera, gl::Model &model): camera{camera}, model{model} {
    }

    void run(gl::MousePosition position) override {
        std::cout << "X: " << position.x << ", Y: " << position.y << std::endl;
    }

protected:
    gl::Camera &camera;
    gl::Model &model;
};

class OffsetChangeCallback: public gl::Callback<gl::MousePositionOffset> {
public:
    explicit OffsetChangeCallback(gl::Camera &camera, gl::Model &model): camera{camera}, model{model} {
    }


    void run(gl::MousePositionOffset offset) override {
        std::cout << "X Offset: " << offset.x << ", Y Offset: " << offset.y << std::endl;

        camera.yaw += offset.x;
        camera.pitch += offset.y;
    }

protected:
    gl::Camera &camera;
    gl::Model &model;
};