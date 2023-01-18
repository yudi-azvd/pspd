#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init_arr(int* arr, int size) {
    for (size_t i = 0; i < size; i++) {
        if (rand() % 11 == 0)
            arr[i] = 0;
        else
            arr[i] = rand();
    }
}

int main() {
    const int SIZE = 100000000;

    int* arr = malloc(sizeof(int) * SIZE);
    int nzeros = 0;

    init_arr(arr, SIZE);

    for (size_t i = 0; i < SIZE; i++) {
        if (arr[i] == 0)
            nzeros++;
    }

    printf("Zeros count: %d\n", nzeros);
}