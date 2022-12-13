#include "../a-rpc-1-worker/util.h"
#include "darray.h"
#include "hashtable.h"

#include <stdio.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("usage: %s <file path>\n", argv[0]);
        exit(1);
    }

    Darray* d = read_from_file(argv[1]);
    HT* ht = HT_create();

    for (int i = 0; i < d->size; i++) {
        int word_count = HT_get(ht, d->arr[i]);
        if (word_count == _HT_ITEM_NULL_VAL) {
            HT_put(ht, d->arr[i], 1);
        } else {
            HT_put(ht, d->arr[i], word_count+1);
        }
    }

    HT_print(ht);

    HT_destroy(ht);
    Darray_destroy_deep(d);
    return 0;
}