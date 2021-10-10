#include "callback.h"


template<class T>
gl::Control<T>::Control(): callbacks{} {
}

template<class T>
gl::Control<T>::~Control() noexcept {
    std::for_each(callbacks.begin(), callbacks.end(), [](Callback<T> *callback) {
        callback->control = nullptr;
    });
    callbacks.clear();
}

template<class T>
void gl::Control<T>::unregisterCallback(gl::Callback<T> *callback) {
    callbacks.erase(callback);
    callback->control = nullptr;
}

template<class T>
void gl::Control<T>::registerCallback(gl::Callback<T> *callback) {
    callbacks.insert(callback);

    if (callback->control != nullptr) {
        callback->control->unregisterCallback(callback);
    }

    callback->control = this;
}

template<class T>
gl::Callback<T>::Callback(): control{nullptr} {
}

template<class T>
gl::Callback<T>::~Callback() noexcept {
    if (control != nullptr) {
        control->unregisterCallback(this);
    }
}

template<class T>
void gl::Callback<T>::run(T value) {
}
