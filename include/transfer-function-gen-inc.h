#ifndef OPENGLBOILERPLATE_TRANSFER_FUNCTION_GEN_INC_H
#define OPENGLBOILERPLATE_TRANSFER_FUNCTION_GEN_INC_H

#include "transfer-function-gen.h"

#include <fstream>
#include <limits>

template<class T>
gl::TransferFunctionGen<T>::TransferFunctionGen() = default;

template<class T>
gl::TransferFunctionGen<T>::~TransferFunctionGen() = default;

template<class T>
void gl::TransferFunctionGen<T>::generate(const std::string &path) {
    auto min = std::numeric_limits<T>::min();
    auto max = std::numeric_limits<T>::max();

    const auto size = max - min + 1;
    const auto buffer_size = size * 4;

    std::unique_ptr<unsigned char> buffer{new unsigned char[buffer_size]};
    std::memset(buffer.get(), 0, buffer_size * sizeof(unsigned char));

    for (long long i = 0; i < size; i++) {
        auto vec4 = run((T)(min + i));

        buffer.get()[4 * i] = (unsigned char)(vec4.x * 255);
        buffer.get()[4 * i + 1] = (unsigned char)(vec4.y * 255);
        buffer.get()[4 * i + 2] = (unsigned char)(vec4.z * 255);
        buffer.get()[4 * i + 3] = (unsigned char)(vec4.w * 255);
    }

    std::ofstream out_file{path, std::ios::binary | std::ios::out};
    if (!out_file.is_open()) {
        throw std::runtime_error{"Can't open file"};
    }

    out_file.write(reinterpret_cast<char*>(buffer.get()), buffer_size * sizeof(signed char));
    out_file.close();
}

#endif //OPENGLBOILERPLATE_TRANSFER_FUNCTION_GEN_INC_H
