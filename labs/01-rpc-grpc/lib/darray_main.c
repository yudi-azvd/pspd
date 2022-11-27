#include "darray.h"
#include <stdio.h>

int main() {
    Darray* darr = Darray_create();
    char* strings[] = {
        "lorem",
        "ipsum",
        "coisa",
        "alem",
    };

    for (int i = 0; i < 4; i++) {
        // darr->arr[i] = strings[i];
        Darray_append(darr, strings[i]);
    }

    for (int i = 0; i < 4; i++) {
        printf("string %s\n", darr->arr[i]);
    }

    // arr->arr[i] = strings[i];

    Darray_destroy(darr);
    return 0;
}