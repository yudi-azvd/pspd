#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_arr(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        printf(". Thread %d: %d\n", i, arr[i]);
    }
    printf("\n");
}

int main() {
    const int SIZE = 100000000;
    // omp_set_num_threads(4);
    // int nthreads = omp_get_max_threads();

    int* arr = malloc(sizeof(int) * SIZE);
    int nzeros = 0;

    for (size_t i = 0; i < SIZE; i++) {
        if (rand() % 11 == 0)
            arr[i] = 0;
        else
            arr[i] = rand();
    }

    #pragma omp parallel for
    for (size_t i = 0; i < SIZE; i++) {
        if (arr[i] == 0)
            #pragma omp critical
            nzeros++;
    }

    printf("Zeros count: %d\n", nzeros);
}