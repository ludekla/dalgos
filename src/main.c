#include <stdio.h>

#include "ch12_sort.h"

int compare_ints(const void* key1, const void* key2) {
    return (*(int*)key1 > *(int*)key2);
}

void print_ints(int* arr, int size) {
    printf("{");
    for (int i = 0; i < size; i++)
        printf(" %d", *(arr + i));
    printf(" }\n");
}

int main() {

    int data[6] = {5, 2, 4, 6, 1, 3};
    
    print_ints(data, 6);
    // perform insertion sort
    insertion_sort(data, 6, sizeof(int), compare_ints);
    print_ints(data, 6);

    return 0;
}
