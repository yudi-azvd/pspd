#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 500000

void print_arr_sum(int* a, int* b, int* c, int size) {
    for (int i = 0; i < size; i++) {
        printf("[%d]: %d + %d = %d\n", i, a[i], b[i], c[i]);
    }
    printf("\n");
}

int main(int argc, char* argv[]) {
    omp_set_num_threads(4);
    int nthreads = omp_get_max_threads();
    int a[SIZE], b[SIZE], c[SIZE];
    int total = 0;

    for (size_t i = 0; i < SIZE; i++) {
        a[i] = 0;
        b[i] = 1;
    }

#pragma omp parallel
    {
        int total_local = 0;
#pragma omp parallel for
        for (size_t i = 0; i < SIZE; i++) {
            c[i] = b[i] + a[i];
            total_local += c[i];
        }
#pragma omp atomic
        total += total_local;
    }

    printf("total %d\n", total);
    return 0;
}
