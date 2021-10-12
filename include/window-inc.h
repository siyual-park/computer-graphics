#ifndef OPENGLBOILERPLATE_WINDOW_INC_H
#define OPENGLBOILERPLATE_WINDOW_INC_H

#include "window.h"

template<class T>
void gl::Window::addListener(gl::EventListener<T> listener) {
    event_emitter.addListener(listener);
}


#endif //OPENGLBOILERPLATE_WINDOW_INC_H
