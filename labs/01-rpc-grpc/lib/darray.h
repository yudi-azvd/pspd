#ifndef DARRAY_H_INCLUDED
#define DARRAY_H_INCLUDED

#include <stdlib.h>
#include <string.h>

#define _DARRAY_INITIAL_CAPACITY 4

typedef struct Darray {
    int size;
    int capacity;
    char** arr;
} Darray;

Darray* Darray_create() {
    Darray* darray = (Darray*)calloc(1, sizeof(Darray));
    darray->size = 0;
    darray->capacity = _DARRAY_INITIAL_CAPACITY;
    darray->arr = (char**)calloc(_DARRAY_INITIAL_CAPACITY, sizeof(char**));
    return darray;
}

void Darray_destroy(Darray* darr) {
    for (size_t i = 0; i < darr->size; i++)
        free(darr->arr[i]);
    free(darr->arr);
    free(darr);
}

void Darray_append(Darray* darr, char* str) {
    int str_len = strlen(str);
    darr->arr[darr->size] = calloc((str_len + 1), sizeof(char));
    memcpy(darr->arr[darr->size], str, str_len);
    darr->size++;
}

#endif // DARRAY_H_INCLUDED