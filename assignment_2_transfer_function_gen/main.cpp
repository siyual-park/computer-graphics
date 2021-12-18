#include <cmath>
#include "transfer-function-gen.h"

class TransferFunctionGen : public gl::TransferFunctionGen<signed short> {
protected:
    glm::vec4 run(signed short value) override {
        float alpha = 0.0f;

        if (value < min) {
            alpha = 0.0f;
        } else if (value > max) {
            alpha = 1.0f;
        } else {
            auto width = (float) (max - min);
            alpha = 0.0f * (float) std::abs(value - max) / width + 1.0f * (float) std::abs(value - min) / width;
        }

        return glm::vec4(1.0f, 1.0f, 1.0f, alpha);
    }

private:
    const signed short min{119};
    const signed short max{325};
};

int main() {
    TransferFunctionGen{}.generate("./resources/objects/volume/tf.raw", gl::ENDIAN_TYPE::BIG);
    return 0;
}