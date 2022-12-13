#ifndef DARRAY_H_INCLUDED
#define DARRAY_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _DARRAY_INITIAL_CAPACITY 4
#define MAX_LINE_BYTES 1000

typedef struct Darray {
    int size;
    int capacity;
    char** arr;
} Darray;

void _Darray_resize(Darray* darr, int new_capacity);
void Darray_append(Darray* darr, char* str);

Darray* Darray_create() {
    Darray* darray = (Darray*)calloc(1, sizeof(Darray));
    darray->size = 0;
    darray->capacity = _DARRAY_INITIAL_CAPACITY;
    darray->arr = (char**)calloc(_DARRAY_INITIAL_CAPACITY, sizeof(char**));
    return darray;
}

void Darray_append_from_str(Darray* darray, char* str) {
    char buffer_copy[MAX_LINE_BYTES] = "\0";
    strncpy(buffer_copy, str, strlen(str));
    char* delimeters = " \t\n";
    char* last_word_found = NULL;
    last_word_found = strtok(buffer_copy, delimeters);
    while (last_word_found != NULL) {
        size_t word_len = strlen(last_word_found);
        char* word = (char*) calloc(word_len + 1, sizeof(char));
        strncpy(word, last_word_found, word_len);
        Darray_append(darray, word);
        last_word_found = strtok(NULL, delimeters);
    }
}

void Darray_destroy(Darray* darr) {
    free(darr->arr);
    free(darr);
}

void Darray_destroy_deep(Darray* darr) {
    for (size_t i = 0; i < darr->size; i++)
        free(darr->arr[i]);
    free(darr->arr);
    free(darr);
}

void Darray_append(Darray* darr, char* str) {
    if (darr->size + 1 >= darr->capacity) {
        _Darray_resize(darr, darr->capacity * 2);
    }
    darr->arr[darr->size] = str;
    darr->size++;
}

/**
 * Na grande maioria dos casos, esse resize é pra _aumentar_ a capacidade do
 * array. Então or enquanto não precisa verificar se new_capacity é maior ou
 * menor que capacity.
 */
void _Darray_resize(Darray* darr, int new_capacity) {
    darr->arr = realloc(darr->arr, new_capacity * sizeof(char**));
    darr->capacity = new_capacity;
}

#endif // DARRAY_H_INCLUDED