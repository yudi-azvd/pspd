#include <omp.h>
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
    omp_set_num_threads(4);
    int nthreads = omp_get_max_threads();

    int* arr = malloc(sizeof(int) * SIZE);
    int nzeros = 0, nzeros_local = 0;

    init_arr(arr, SIZE);
    
#pragma omp parallel private(nzeros_local)
    {
        nzeros_local = 0;
#pragma omp for
        for (size_t i = 0; i < SIZE; i++) {
            if (arr[i] == 0)
                nzeros_local++;
        }
// #pragma omp atomic
//         nzeros += nzeros_local;
#pragma omp critical
        { nzeros += nzeros_local; }
    }

    printf("Zeros count: %d\n", nzeros);
}