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
//        camera.yaw += offset.x * 0.01;
//        camera.pitch += offset.y * 0.01;
    }

protected:
    gl::Camera &camera;
    gl::Model &model;
};