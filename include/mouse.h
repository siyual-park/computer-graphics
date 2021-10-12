#ifndef OPENGLBOILERPLATE_MOUSE_H
#define OPENGLBOILERPLATE_MOUSE_H

#include "event.h"

namespace gl {
    struct MousePositionEvent {
        double x;
        double y;
    };

    struct MousePositionOffsetEvent {
        double x;
        double y;
    };

    struct MouseButtonEvent {
        int button;
        int action;
    };

    struct ScrollOffset {
        double x;
        double y;
    };

    class MousePositionOffsetEventProvider: public EventListener<MousePositionEvent> {
    public:
        explicit MousePositionOffsetEventProvider(EventEmitter &event_emitter);

        void on(MousePositionEvent event) override;

    private:
        bool first = true;
        MousePositionEvent last{};

        EventEmitter &event_emitter;
    };
}

#endif //OPENGLBOILERPLATE_MOUSE_H
