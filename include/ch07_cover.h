#ifndef COVER_H
#define COVER_H

#include "ch07_set.h"

int best_subset(Set* set, Set* subsets, Set** best);

int min_cover(Set* set, Set* subsets, Set* cover);

#endif
