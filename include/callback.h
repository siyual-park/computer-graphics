#ifndef OPENGLBOILERPLATE_CALLBACK_H
#define OPENGLBOILERPLATE_CALLBACK_H

namespace gl {
    template <class T>
    class Callback {
    public:
        Callback();
        virtual ~Callback() noexcept;

        virtual void run(T value);
    };
}

#include "callback-inc.h"

#endif //OPENGLBOILERPLATE_CALLBACK_H
