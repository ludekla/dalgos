#include <stdlib.h>
#include <string.h>

#include "ch06_queue.h"
#include "ch06_event.h"

void event_init(Event* event, event_t type, char* food) {
    event->type = type;
    event->food = food;
}

int receive_event(Queue* queue, const Event* event) {
    Event* new_event = (Event*)malloc(sizeof(Event));
    // copy event
    // void* memcpy(void* restrict to, void* restrict from, size_t size)
    memcpy(new_event, event, sizeof(Event));
    // put it in the queue
    if (queue_enqueue(queue, new_event) != 0)
        return -1; // failure
    // success
    return 0;
}

int process_event(Queue* queue, void (*dispatch_fn)(Event* event)) {
    Event* event;
    // get the event from the queue
    if (queue_dequeue(queue, (void**)&event) != 0)
        return -1; // failure
    // process it
    dispatch_fn(event);
    // deallocate
    free(event);
    // success    
    return 0;
}

