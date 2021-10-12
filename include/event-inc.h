#ifndef OPENGLBOILERPLATE_EVENT_INC_H
#define OPENGLBOILERPLATE_EVENT_INC_H

#include "event.h"

template<class T>
void gl::EventEmitter::emit(T event) {
    auto it = listeners.find(typeid(T));

    if (it == listeners.end()) {
        return;
    }

    std::set<BaseListener*> current_listeners = it->second;
    for (BaseListener* listener : current_listeners) {
        reinterpret_cast<EventListener<T>*>(listener)->on(event);
    }
}

template<class T>
void gl::EventEmitter::addListener(gl::EventListener<T> &listener) {
    auto it = listeners.find(typeid(T));

    if (it == listeners.end()) {
        listeners[typeid(T)] = std::set<BaseListener*>{ &listener };
    } else {
        std::set<BaseListener*> current_listeners = it->second;
        current_listeners.insert(&listener);
        listeners[typeid(T)] = current_listeners;
    }
}

#endif //OPENGLBOILERPLATE_EVENT_INC_H
