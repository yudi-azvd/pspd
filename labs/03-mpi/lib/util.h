#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

#include "../lib/darray.h"
#include <stdlib.h>

#define MAX_CONTENT_BYTES 100001
#define BUFFER_BYTES_INITIAL 128
#define BUFFER_BYTES_MAX 10'000'000

char buffer[MAX_CONTENT_BYTES];

Darray* read_from_file(FILE* fp, size_t buffer_size) {
    char buffer_copy[MAX_CONTENT_BYTES];
    Darray* darr = Darray_create();
    while (fgets(buffer, buffer_size, fp) != NULL) {
        Darray_append_from_str(darr, buffer);
    }

    return darr;
}

#endif // UTIL_H_INCLUDED