#include <stdio.h>

#include "ch08_ohtable.h"

int match_ints(const void* data1, const void* data2) {
    return *(int*)data1 == *(int*)data2;
}

int hashf_1(void* key) {
    int* p = (int*)key;
    int coding = *p * 1699 + 3; 
    return coding;
}

int hashf_2(void* key) {
    int* p = (int*)key;
    int coding = *p * 123 + 4; 
    return coding;
}

void ohtable_print(OHTable* tb) {
    printf("Hash Table [size %02d] {\n", tb->size);
    for (int i = 0; i < tb->n_positions; i++) {
        printf("%2d:", i + 1);
        if (tb->table[i])
            printf("%d ", *(int*)tb->table[i]);
        else
            printf("- ");
    }
    printf("\n}\n");
}

void print_insert_response(int response) {
    printf("Response r: %d (meaning: ", response);
    switch (response) {
        case 0:
            printf("Insertion Success)\n");
            break;
        case 1:
            printf("Insertion Failure, key already exists)\n");
            break;
        case -1:
            printf("Insertion Failure, sth went wrong)\n");
    }
}

int main() {

    int a[12] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};


    OHTable tb;
    ohtable_init(&tb, 15, hashf_1, hashf_2, match_ints, NULL);

    for (int i = 0; i < 12; i++) {
        ohtable_insert(&tb, a + i);
    }

    ohtable_print(&tb);

    void* data;
    
    printf("Delete 7\n");
    data = a + 7;
    ohtable_remove(&tb, &data);
    ohtable_print(&tb);
    
    printf("Delete 1\n");
    data = a + 1;
    ohtable_remove(&tb, &data);
    ohtable_print(&tb);
    
    printf("Try to insert 2\n");
    int r = ohtable_insert(&tb, a + 2);
    print_insert_response(r);

    printf("Try to insert 7\n");
    r = ohtable_insert(&tb, a + 7);
    print_insert_response(r);

    ohtable_print(&tb);
  
    printf("Look up 6: ");
    data = a + 6;
    r = ohtable_lookup(&tb, &data);
    printf("response is %d (0 success, -1 failure)\n", r);

    // clean up
    ohtable_clear(&tb);

    return 0;
}

