#ifndef EVENT_H
#define EVENT_H

#include "ch06_queue.h"

typedef enum {
    BREAKFAST,
    LUNCH,
    SUPPER
} event_t;

typedef struct {
    event_t type;
    char* food;
} Event;

void event_init(Event* event, event_t type, char* food);

int receive_event(Queue* queue, const Event* event);

int process_event(Queue* queue, void (*dispatch_fn)(Event* event));

#endif
