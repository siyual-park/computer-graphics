#include <iostream>

#include "callback.h"
#include "mouse.h"

class PositionPrintCallback: public gl::Callback<gl::MousePosition> {
public:
    void run(gl::MousePosition position) override {
        std::cout << "X: " << position.x << ", Y: " << position.y << std::endl;
    }
};

class OffsetPrintCallback: public gl::Callback<gl::MousePositionOffset> {
public:
    void run(gl::MousePositionOffset position) override {
        std::cout << "X Offset: " << position.x << ", Y Offset: " << position.y << std::endl;
    }
};