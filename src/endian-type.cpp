#include "endian-type.h"

#include <cstdint>

gl::ENDIAN_TYPE gl::internal::getEndian() {
    union {
        uint32_t i;
        char c[4];
    } bint = {0x01020304};

    if (bint.c[0] == 1) {
        return ENDIAN_TYPE::BIG;
    } else {
        return ENDIAN_TYPE::LITTLE;
    }
}