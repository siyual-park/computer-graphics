#ifndef OPENGLBOILERPLATE_EVENT_H
#define OPENGLBOILERPLATE_EVENT_H

#include <map>
#include <set>
#include <typeindex>

namespace gl {
    class BaseListener {
    public:
        explicit BaseListener() = default;
        BaseListener(const BaseListener&) = delete;
        BaseListener& operator=(const BaseListener&) = delete;
        virtual ~BaseListener() = default;
    };

    template<class T>
    class EventListener: public BaseListener {
    public:
        virtual void on(T event) {};
    };

    class EventEmitter {
    public:
        template<class T>
        void emit(T event);

        template<class T>
        void addListener(EventListener<T> &listener);

    protected:
        std::map<std::type_index, std::set<BaseListener*>> listeners{};
    };
}

#include "event-inc.h"

#endif //OPENGLBOILERPLATE_EVENT_H
