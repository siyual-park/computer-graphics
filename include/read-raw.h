#ifndef OPENGLBOILERPLATE_READ_RAW_H
#define OPENGLBOILERPLATE_READ_RAW_H

#include <string>
#include <memory>
#include "endian-type.h"

namespace gl {
    template<class T>
    std::unique_ptr<T> readRaw(const std::string &path, std::size_t size, ENDIAN_TYPE endian_type = ENDIAN_TYPE::LITTLE);
}

#include "read-raw-inc.h"

#endif //OPENGLBOILERPLATE_READ_RAW_H
