#ifndef OPENGLBOILERPLATE_CONTROL_H
#define OPENGLBOILERPLATE_CONTROL_H

#include <set>
#include <callback.h>

namespace gl {
    template <class T>
    class Control {
    public:
        Control();
        virtual ~Control() noexcept;

        void unregisterCallback(Callback<T> *callback);
        void registerCallback(Callback<T> *callback);

        std::set<Callback<T>*> callbacks;
    };
}

#include "control-inc.h"

#endif //OPENGLBOILERPLATE_CONTROL_H
