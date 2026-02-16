#include <stdlib.h> // malloc
#include <string.h> // memcpy
#include <stdio.h>
#include "ch12_sort.h"

int insertion_sort(void* data, int size, int esize, match_f compare) {
    char* a = (char*)data;
    char* key;
    // Allocate space for key pointer
    if ((key = (char*)malloc(esize)) == NULL)
        return -1;
    int j;
    for (int i = 1; i < size; i++) {
        memcpy(key, a + i * esize, esize);
        j = i - 1;
        while (j >= 0 && compare(a + j * esize, key) > 0) {
            memcpy(a + (j + 1) * esize, a + j * esize, esize);
            j--;
        }
        memcpy(a + (j + 1) * esize, key, esize);
    }
    // clean up
    free(key);
    return 0;
}

    
