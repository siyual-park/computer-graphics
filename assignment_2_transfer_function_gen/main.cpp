#include <cmath>
#include "transfer-function-gen.h"

class TransferFunctionGen : public gl::TransferFunctionGen<signed short> {
public:
    TransferFunctionGen(float alphaMin, float alphaMax): alphaMin{alphaMin}, alphaMax{alphaMax} {}
protected:
    glm::vec4 run(signed short value) override {
        float alpha;

        if (value < min) {
            alpha = alphaMin;
        } else if (value > max) {
            alpha = alphaMax;
        } else {
            auto width = (float) (max - min);
            alpha = alphaMin * (float) std::abs(value - max) / width + alphaMax * (float) std::abs(value - min) / width;
        }

        return glm::vec4(1.0f, 1.0f, 1.0f, alpha);
    }

private:
    const float alphaMin{0.0f};
    const float alphaMax{1.0f};

    const signed short min{119};
    const signed short max{325};
};


int main() {
    TransferFunctionGen{0.0f, 0.2f}.generate("./resources/objects/volume/tf.raw");
    return 0;
}