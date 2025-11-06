#include <stdio.h>

#include "ch05_list.h"
#include "ch06_event.h"
#include "ch06_queue.h"

void dispatch(Event* event) {
    switch (event->type) {
        case BREAKFAST:
            printf("Having %s for breakfast ...\n", event->food);
            break;
        case LUNCH:
            printf("Having %s for lunch ...\n", event->food);
            break;
        case SUPPER:
            printf("Having %s for supper ...\n", event->food);
    }
}

int main() {

    Queue queue;

    queue_init(&queue, NULL);
   
    EventType events[3] = {BREAKFAST, LUNCH, SUPPER};
    char* food[3] = {"porridge", "miso soup", "bread & butter"};

    // enqueue events
    for (int i = 0; i < 3; i++) {
        Event event;
        event_init(&event, events[i], food[i]); 
        if (receive_event(&queue, &event) != 0)
            printf("WARNING: cannot enqueue event %d\n", i);
    }

    // dequeue and process
    while (queue_size(&queue) > 0) {
        if (process_event(&queue, dispatch) != 0)
            printf("Failed to dispatch event\n");
    }

    queue_clear(&queue);

    return 0;
}

