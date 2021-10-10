#ifndef OPENGLBOILERPLATE_CALLBACK_H
#define OPENGLBOILERPLATE_CALLBACK_H

#include <set>

namespace gl {
    template <class T>
    class Callback;

    template <class T>
    class Control {
    public:
        Control();
        virtual ~Control() noexcept;

        void unregisterCallback(Callback<T> *callback);
        void registerCallback(Callback<T> *callback);

        std::set<Callback<T>*> callbacks;
    };

    template <class T>
    class Callback {
    public:
        Callback();
        virtual ~Callback() noexcept;

        Control<T> *control = nullptr;

        virtual void run(T value);
    };
}


#endif //OPENGLBOILERPLATE_CALLBACK_H
