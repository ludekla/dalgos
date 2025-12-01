#include <stdio.h>
#include <string.h> // memcpy

#include "ch10_pqueue.h"

typedef struct {
    int id;
    char* addressee;
} Parcel;

void parcel_init(Parcel* pcl, int id, char* addressee) {
    pcl->id = id;
    pcl->addressee = addressee;
}

int put_parcel(PQueue* pq, Parcel* pcl) {
    if (pqueue_insert(pq, (const void*)pcl) != 0)
        return -1;
    return 0;
}

int get_parcel(PQueue* pq, Parcel* pcl) {
    Parcel* p;
    if (pqueue_extract(pq, (void**)&p) != 0)
        return -1;
    memcpy(pcl, p, sizeof(Parcel));
    return 0;
}

void parcel_print(Parcel* pcl) {
    printf(
        "Parcel { id: %d, addressee: %s }\n", 
        pcl->id, pcl->addressee
    );
}

