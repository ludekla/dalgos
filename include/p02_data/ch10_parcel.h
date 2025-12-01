#ifndef PARCEL_H
#define PARCEL_H

#include "ch10_pqueue.h"

typedef struct {
    int id;
    char* addressee;
} Parcel;

void parcel_init(Parcel* pcl, int id, char* addressee);

void parcel_print(Parcel* pcl);

#define parcel_who(pcl) ((pcl)->addressee)

int put_parcel(PQueue* pq, Parcel* pcl);

int get_parcel(PQueue* pq, Parcel* pcl);

#endif
