#include "darray.h"
#include <stdio.h>

int main() {
    Darray* darr = Darray_create();
    Darray_append_from_str(darr, "lorem ipsum\t5\ncoisa alem 3");
    Darray_append_from_str(darr, "lorem ipsum");

    for (int i = 0; i < darr->size; i++) {
        printf("darr str: %s\n", darr->arr[i]);
    }
    printf("darr size: %d\n", darr->size);
    printf("darr capc: %d\n", darr->capacity);

    Darray_destroy_deep(darr);
    return 0;
}