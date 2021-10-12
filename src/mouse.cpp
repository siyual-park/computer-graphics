#include "mouse.h"

gl::MousePositionOffsetEventProvider::MousePositionOffsetEventProvider(gl::EventEmitter &event_emitter): event_emitter{event_emitter} {

}

void gl::MousePositionOffsetEventProvider::on(gl::MousePositionEvent event) {
    if (first) {
        last = event;
        first = false;
        return;
    }

    gl::MousePositionOffsetEvent offset = {
            .x = event.x - last.x,
            .y = last.y - event.y
    };

    event_emitter.emit(offset);

    last = event;
}


