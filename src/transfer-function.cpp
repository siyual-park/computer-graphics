#include "transfer-function.h"

gl::TransferFunction::TransferFunction(std::size_t size): size{size} {
    data = new float[size];
}

gl::TransferFunction::TransferFunction(gl::TransferFunction &other) noexcept:
        size{other.size}
{
    data = new float[size];
    for (auto i = 0; i < size; i++) {
        data[i] = other.data[i];
    }
}

gl::TransferFunction::TransferFunction(gl::TransferFunction &&other) noexcept:
        size{other.size},
        data{other.data}
{
    other.size = 0;
    other.data = nullptr;
}

gl::TransferFunction::~TransferFunction() {
    size = 0;

    if (data != nullptr) {
        delete data;
        data = nullptr;
    }
}
