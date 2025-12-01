#ifndef PQUEUE_H
#define PQUEUE_H

#include "ch10_heap.h"

typedef Heap PQueue;

#define pqueue_init heap_init

#define pqueue_clear heap_clear

#define pqueue_insert heap_insert

#define pqueue_extract heap_extract

#define pqueue_size(pq) ((pq)->size)

#define pqueue_peek(pq) ((pq)->tree == NULL ? NULL : (pq)->tree[0])

#endif
