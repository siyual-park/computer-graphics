#include <iostream>

#include "callback.h"
#include "mouse.h"

class PositionPrintCallback: public gl::Callback<gl::MousePosition> {
public:
    void run(gl::MousePosition position) override {
        std::cout << "X: " << position.x << ", Y: " << position.y << std::endl;
    }
};