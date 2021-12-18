#ifndef OPENGLBOILERPLATE_TRANSFER_FUNCTION_GEN_H
#define OPENGLBOILERPLATE_TRANSFER_FUNCTION_GEN_H

#include <string>
#include <glm/glm.hpp>

#include "endian-type.h"

namespace gl {
    template<class T>
    class TransferFunctionGen {
    public:
        explicit TransferFunctionGen();
        virtual ~TransferFunctionGen();

        void generate(const std::string &path, ENDIAN_TYPE endian_type = ENDIAN_TYPE::LITTLE);

    protected:
        virtual glm::vec4 run(T value) = 0;
    };
}

#include "transfer-function-gen-inc.h"

#endif //OPENGLBOILERPLATE_TRANSFER_FUNCTION_GEN_H
