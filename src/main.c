#include <stdio.h>

#include "ch10_heap.h"

int compare_ints(const void* data1, const void* data2) {
    return *(int*)data1 - *(int*)data2;
}

void heap_print(Heap* hp) {
    for (int i = 0; i < hp->size; i++)
         printf(" %d", *(int*)hp->tree[i]);
    printf("\n");
}

int main() {

    int a[12] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

    Heap hp;
    heap_init(&hp, compare_ints, NULL);

    for (int i = 0; i < 12; i++) {
        heap_insert(&hp, a + i);
        heap_print(&hp);
    }

    heap_print(&hp);

    int* p;
    printf("Extract:\n");
    for (int i = 0; i < 12; i++) {
        heap_extract(&hp, (void**)&p);
        printf(" %d", *p);
    }
    printf("\n");

    // clean up
    heap_clear(&hp);

    return 0;
}

