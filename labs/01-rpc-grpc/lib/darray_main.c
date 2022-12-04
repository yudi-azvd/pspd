#include "darray.h"
#include <stdio.h>

int main() {
    Darray* darr = Darray_create();
    int len = 4;
    char* strings[] = {
        "lorem",
        "ipsum",
        "coisa",
        "alem",
    };

    for (int i = 0; i < len; i++) {
        Darray_append(darr, strings[i]);
    }

    for (int i = 0; i < darr->size; i++) {
        printf("string %s\n", darr->arr[i]);
    }

    Darray_destroy(darr);
    return 0;
}