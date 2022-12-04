#include "../lib/darray.h"
#include "util.h"

#include <stdio.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("usage: %s <file path>\n", argv[0]);
        exit(1);
    }

    Darray* darr = read_from_file(argv[1]);

    for (int i = 0; i < darr->size; i++) {
        printf("darr str: %s\n", darr->arr[i]);
    }
    printf("---\n");
    printf("darr size: %d\n", darr->size);
    printf("darr capc: %d\n", darr->capacity);

    Darray_destroy_deep(darr);
    return 0;
}