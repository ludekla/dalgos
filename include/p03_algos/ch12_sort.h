
typedef int (*match_f)(const void* key1, const void* key2);

int insertion_sort(void* data, int size, int esize, match_f compare);
