#ifndef OHTABLE_H
#define OHTABLE_H

#include <stdlib.h>
#include <string.h>

typedef struct {
    int size;
    int n_positions;
    void** table; // array of generic pointers
    // function pointers
    int (*hash_1)(void* data);
    int (*hash_2)(void* data);
    int (*match)(const void* data1, const void* key2);
    void (*purge)(void* data);
} OHTable;

int ohtable_init(
    OHTable* tb,
    int n_positions,
    int (*hash_1)(void* key),
    int (*hash_2)(void* key),
    int (*match)(const void* key1, const void* key2),
    void (*purge)(void* data)
);

int ohtable_insert(OHTable* tb, void* data);

int ohtable_remove(OHTable* tb, void** data);

int ohtable_lookup(OHTable* tb, void** data);

void ohtable_clear(OHTable* tb);

#define ohtable_size(tb) ((tb)->size)

#endif
