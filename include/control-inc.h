#ifndef OPENGLBOILERPLATE_CONTROL_INC_H
#define OPENGLBOILERPLATE_CONTROL_INC_H

#include "control.h"

template<class T>
gl::Control<T>::Control(): callbacks{} {
}

template<class T>
gl::Control<T>::~Control() noexcept {
    callbacks.clear();
}

template<class T>
void gl::Control<T>::unregisterCallback(gl::Callback<T> *callback) {
    callbacks.erase(callback);
}

template<class T>
void gl::Control<T>::registerCallback(gl::Callback<T> *callback) {
    callbacks.insert(callback);
}

#endif //OPENGLBOILERPLATE_CONTROL_INC_H
