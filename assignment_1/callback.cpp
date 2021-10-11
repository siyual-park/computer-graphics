#include <iostream>

#include "callback.h"
#include "mouse.h"
#include "model.h"

class PositionChangeCallback: public gl::Callback<gl::MousePosition> {
public:
    explicit PositionChangeCallback(gl::Model &model): model{model} {
    }

    void run(gl::MousePosition position) override {
        std::cout << "X: " << position.x << ", Y: " << position.y << std::endl;
    }

protected:
    gl::Model &model;
};

class OffsetChangeCallback: public gl::Callback<gl::MousePositionOffset> {
public:
    explicit OffsetChangeCallback(gl::Model &model): model{model} {
    }


    void run(gl::MousePositionOffset position) override {
        std::cout << "X Offset: " << position.x << ", Y Offset: " << position.y << std::endl;
    }

protected:
    gl::Model &model;
};