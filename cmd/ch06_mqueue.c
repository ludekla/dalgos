#include <stdio.h>

//#include "ch05_list.h"
#include "ch06_queue.h"

void purge(void* v) {
    int* p = (int*)v;
    printf("Not really purging: %d\n", *p);
}

int main() {

    Queue queue;

    queue_init(&queue, purge);
   
    int a[3] = {0, 1, 2};

    
    for (int i = 0; i < 3; i++) {
        int size = queue_size(&queue);
        printf("Queue size before enqueueing: %u\n", size);
        queue_enqueue(&queue, a + i);
        size = queue_size(&queue);
        printf("Queue size after enqueueing: %u\n", size);
    }
    
    int* data;
    
    if ((data = (int*)queue_peek(&queue)) != NULL)
        printf("Peek: %d\n", *data); 
    
    while ((queue_dequeue(&queue, (void**)&data) == 0)) {
        int size = queue_size(&queue);
        printf("Successfully dequeued: %d (size now: %u)\n", *data, size);
        if ((data = (int*)queue_peek(&queue)) != NULL)
            printf("Peek: %d\n", *data); 
    }

    queue_clear(&queue);

    return 0;
}

