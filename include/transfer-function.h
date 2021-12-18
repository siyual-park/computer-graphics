#ifndef OPENGLBOILERPLATE_TRANSFER_FUNCTION_H
#define OPENGLBOILERPLATE_TRANSFER_FUNCTION_H

#include <cstddef>

namespace gl {
    class TransferFunction {
    public:
        explicit TransferFunction(std::size_t size);
        TransferFunction(TransferFunction &other) noexcept;
        TransferFunction(TransferFunction &&other) noexcept;
        ~TransferFunction();

        unsigned char* data{};
        std::size_t size;
    };
}


#endif //OPENGLBOILERPLATE_TRANSFER_FUNCTION_H
