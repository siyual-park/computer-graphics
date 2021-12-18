#ifndef OPENGLBOILERPLATE_ENDIAN_TYPE_H
#define OPENGLBOILERPLATE_ENDIAN_TYPE_H

namespace gl {
    enum class ENDIAN_TYPE {
        LITTLE,
        BIG
    };

    namespace internal {
        template <class T>
        void copyData(const T* source, T *target, std::size_t size) noexcept {
            for (auto i = 0; i < size; ++i) {
                target[i] = source[i];
            }
        }

        template <typename DATA>
        void convertToBidEndian(DATA *data) noexcept {
            union {
                DATA f;
                unsigned char c8[sizeof(DATA)];
            } source, dest;
            for (auto i = 0; i < sizeof(DATA); ++i) {
                source.f = data[i];
                for (auto k = 0; k < sizeof(DATA); ++k)
                    dest.c8[k] = source.c8[sizeof(DATA) - k - 1];
                data[i] = dest.f;
            }
        }
    }
}


#endif //OPENGLBOILERPLATE_ENDIAN_TYPE_H
