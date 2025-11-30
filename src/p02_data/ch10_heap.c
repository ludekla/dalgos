#include <stdlib.h>  // NULL
#include <string.h> // memset
#include <stdarg.h> // variadic macros

#include "ch10_heap.h"

void heap_init(Heap* heap, compare_f compare, purge_f purge) {
    heap->size = heap->cap = 0;
    heap->compare = compare;
    heap->purge = purge;
    heap->tree = NULL;
}

void heap_clear(Heap* heap) {
    if (heap->purge != NULL) {
        for (int i = 0; i < heap->size; i++)
            heap->purge(heap->tree[i]);
    }
    free(heap->tree);
    memset(heap, 0, sizeof(Heap));
}

// helper
static void swap_em(Heap* heap, int i, int j) {
    void* temp = heap->tree[i];
    heap->tree[i] = heap->tree[j];
    heap->tree[j] = temp;
}

int heap_insert(Heap* heap, const void* data) {
    // Need more capacity?
    if (heap->size == heap->cap) {
        void** tree = heap->tree;
        int cap = 2 * (heap->size + 1);
        if ((tree = (void**)realloc(tree, cap * sizeof(void*))) == NULL)  
            return -1;
        heap->cap = cap;
        heap->tree = tree;
    }
    int ipos = heap_size(heap); 
    // place data at the end
    heap->tree[ipos] = (void*)data;
    // reinstate heap property if necessary
    int ppos = heap_parent(ipos);
    while (ipos > 0 && heap->compare(data, heap->tree[ppos]) > 0) {
        // swap'em elements
        swap_em(heap, ipos, ppos);
        // update indices
        ipos = ppos;
        ppos = heap_parent(ipos);
    }
    heap->size++;
    return 0;
}

// helper
static int max_pos(Heap* heap, int n, ...) {
    va_list argptr;
    va_start(argptr, n);
    int m = va_arg(argptr, int);
    int j;
    for (int i = 1; i < n; i++) {
        j = va_arg(argptr, int);
        if (heap->compare(heap->tree[j], heap->tree[m]) > 0)
            m = j;
    }
    return m;
}

int heap_extract(Heap* heap, void** data) {
    if (heap_size(heap) == 0)
        return 1;
    // hand data over
    *data = heap->tree[0];
    // overwrite top position with last element
    heap->tree[0] = heap->tree[heap_size(heap) - 1];
    heap->size--;
    // Go and heapify if need be
    int ipos = 0, lpos = 1, rpos = 2;
    int mpos;
    while (lpos < heap_size(heap)) { 
        // find index of maximum element
        if (rpos < heap_size(heap)) 
            mpos = max_pos(heap, 3, ipos, lpos, rpos); 
        else
            mpos = max_pos(heap, 2, ipos, lpos);
        if (mpos == ipos)
            break;
        swap_em(heap, mpos, ipos);
        ipos = mpos;
        lpos = heap_left(ipos);
        rpos = heap_right(ipos);
    } 
    return 0;
}
