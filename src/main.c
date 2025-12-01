#include <stdio.h>

#include "ch10_parcel.h"
#include "ch10_pqueue.h"

int compare_parcels(const void* pc1, const void* pc2) {
    return ((Parcel*)pc1)->id - ((Parcel*)pc2)->id; 
}

int main() {

    int ids[6] = {3, 4, 2, 1, 0, 5};
    char* names[6] = {"Thomas", "Sarah", "Lutz", "Roland", "Hugh", "Milo"};
    Parcel p[6];

    PQueue queue;
    pqueue_init(&queue, compare_parcels, NULL);

    // Pack parcels and send them
    printf("---------------\nSend Parcels\n---------------\n");
    for (int i = 0; i < 6; i++) {
        parcel_init(p + i, ids[i], names[i]); 
        put_parcel(&queue, p + i);
        printf("Dispatching ...\n");
        parcel_print(p + i);
    }

    // Receive them
    printf("---------------\nReceive Parcels\n---------------\n");

    Parcel pcl;
    while (pqueue_size(&queue) > 0) {
        printf("Peek: ");
        Parcel *pp = (Parcel*)pqueue_peek(&queue);
        printf("parcel for %s, aha ...\n", parcel_who(pp));
        printf("Unpacking parcel ...\n");
        if (get_parcel(&queue, &pcl) != 0) {
            printf("Error unpacking a parcel\n");
            continue;
        }
        parcel_print(&pcl);
    }

    // clean up
    pqueue_clear(&queue);

    return 0;
}

