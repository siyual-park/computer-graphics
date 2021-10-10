#ifndef OPENGLBOILERPLATE_CALLBACK_INC_H
#define OPENGLBOILERPLATE_CALLBACK_INC_H

#include "callback.h"

template<class T>
gl::Callback<T>::Callback() = default;

template<class T>
gl::Callback<T>::~Callback() noexcept = default;

template<class T>
void gl::Callback<T>::run(T value) {
}


#endif //OPENGLBOILERPLATE_CALLBACK_INC_H
