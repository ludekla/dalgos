#ifndef QUEUE_H
#define QUEUE_H

#include "ch05_list.h"

typedef List Queue;

#define queue_init list_init

int queue_enqueue(Queue* queue, void* data);

int queue_dequeue(Queue* queue, void** data);

#define queue_peek(queue) ((queue)->head == NULL ? NULL : (queue)->head->data)

#define queue_clear list_clear

#define queue_size(queue) ((queue)->size)

#endif
