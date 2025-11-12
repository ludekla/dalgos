#include "ch08_ohtable.h"

#include <stdio.h>

int ohtable_init(
    OHTable* tb,
    int n_positions,
    int (*hash_1)(void* data),
    int (*hash_2)(void* data),
    int (*match)(const void* data1, const void* data2),
    void (*purge)(void* data)
) {
    // allocate space for the table
    if ((tb->table = (void**)malloc(n_positions * sizeof(void*))) == NULL)
        // sth went wrong
        return -1;
    tb->size = 0;
    tb->n_positions = n_positions;
    // make sure pointers are pointing nowhere
    for (int i = 0; i < n_positions; i++)
        tb->table[i] = NULL;
    // initialise function pointers
    tb->hash_1 = hash_1;
    tb->hash_2 = hash_2;
    tb->match = match;
    tb->purge = purge;
    // everything is aces
    return 0;
}

int ohtable_insert(OHTable* tb, void* data) {
    if (tb->size == tb->n_positions)
        // table is full
        return -1;
    int hc1 = tb->hash_1(data);
    int hc2 = tb->hash_2(data);
    int pos;
    for (int i = 0; i < tb->n_positions; i++) {
        pos = (hc1 + i*hc2) % tb->n_positions;
        if (tb->table[pos] == NULL) {
            // slot available
            tb->table[pos] = data;
            tb->size++;
            return 0;
        }
        if (tb->match(tb->table[pos], data))
            // data already present
            return 1;
    }
    return -1;
}

int ohtable_remove(OHTable* tb, void** data) {
    int hc1 = tb->hash_1(*data);
    int hc2 = tb->hash_2(*data);
    int pos;
    for (int i = 0; i < tb->n_positions; i++) {
        pos = (hc1 + i*hc2) % tb->n_positions;
        if (tb->match(tb->table[pos], *data)) {
            *data = tb->table[pos];
            tb->table[pos] = NULL;
            tb->size--;
            return 0;
        }
    }
    return -1;
}

int ohtable_lookup(OHTable* tb, void** data) {
    int hc1 = tb->hash_1(*data);
    int hc2 = tb->hash_2(*data);
    int pos;
    for (int i = 0; i < tb->n_positions; i++) {
        pos = (hc1 + i*hc2) % tb->n_positions;
        if (tb->match(tb->table[pos], *data)) {
            *data = tb->table[pos];
            return 0;
        }
    }
    return -1;
}

void ohtable_clear(OHTable* tb) {
    if (tb->purge != NULL) {
        for (int i = 0; i < tb->n_positions; i++)
            tb->purge(tb->table[i]);
    }
    free(tb->table);
    memset(tb, 0, sizeof(OHTable));
}
