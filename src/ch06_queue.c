#include <stdlib.h> // NULL

#include "ch05_list.h"
#include "ch06_queue.h"

int queue_enqueue(Queue* queue, void* data) {
    return list_insert(queue, queue->tail, data);
}

int queue_dequeue(Queue* queue, void** data) {
    return list_remove(queue, NULL, data);
}
