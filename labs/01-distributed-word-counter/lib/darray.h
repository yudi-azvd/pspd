#ifndef DARRAY_H_INCLUDED
#define DARRAY_H_INCLUDED

#include <stdlib.h>

#define _DARRAY_INITIAL_CAPACITY 4

typedef struct Darray {
  int size;
  int capacity;
  char **arr;
} Darray;

Darray *Darray_create() {
  Darray *darray = (Darray *)calloc(1, sizeof(Darray));
  darray->size = 0;
  darray->capacity = _DARRAY_INITIAL_CAPACITY;
  darray->arr = (char **)calloc(_DARRAY_INITIAL_CAPACITY, sizeof(char **));
  return darray;
}

void Darray_destroy(Darray *darr) {
  free(darr->arr);
  free(darr);
}

void Darray_append(Darray *darr, char* str) {
  darr->arr[darr->size++] = str;
}

#endif // DARRAY_H_INCLUDED