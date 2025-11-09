#include <stdio.h>

#include "ch07_set.h"
#include "ch07_cover.h"

int match_ints(const void* data1, const void* data2) {
    return *(int*)data1 == *(int*)data2;
}

int match_subsets(const void* data1, const void* data2) {
    return data1 == data2;
}

void set_print(Set* set) {
    printf("Set {");
    for (Node* run = set->head; run; run = run->next)
        printf(" node: %d", *(int*)run->data);
    printf(" }\n");
}

int insert_ints(Set *set, int* a, int size) {
    for (int i = 0; i < size; i++) {
         if (set_insert(set, a + i) != 0)
            printf("WARNING: cannot insert %d\n", *(a+i));
    }
}

int main() {

    Set set;
    set_init(&set, match_ints, NULL);

    int a[6] = {0, 1, 2, 3, 4, 5};
    insert_ints(&set, a, 6);
    printf("Set:\n");
    set_print(&set);

    Set subsets[5]; 
    
    int small_fry[4][2] = {{0, 1}, {4, 5}, {3, 4}, {1, 2}};
    for (int i = 0; i < 4; i++) {
        set_init(subsets + i, match_ints, NULL);
        insert_ints(subsets + i, small_fry[i], 2);
    }

    int big[3] = {0, 1, 2};
    set_init(subsets + 4, match_ints, NULL);
    insert_ints(subsets + 4, big, 3);

    Set family;
    set_init(&family, match_subsets, NULL);

    for (int i = 0; i < 5; i++) {
        if (set_insert(&family, subsets + i) != 0)
            printf("Cannot insert subset %d\n", i + 1);
    }
    // have a look at the subsets
    printf("Subsets:\n");
    for (Node* run = family.head; run; run = run->next)
        set_print((Set*)run->data);

    Set cover;
    if (min_cover(&set, &family, &cover) != 0)
        printf("ERROR: min_cover failed\n");

    printf("Minimum-size cover:\n");
    for (Node* run = cover.head; run; run = run->next)
        set_print(run->data);

    // clean up (not necessary, no heap alloc)
    for (int i = 0; i < 5; i++)
        set_clear(subsets + i);
    set_clear(&set);

    return 0;
}

