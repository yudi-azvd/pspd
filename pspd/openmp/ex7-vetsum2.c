#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

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

    for (size_t i = 0; i < SIZE; i++) {
        a[i] = rand() % 11;
        b[i] = rand() % 5;
    }

#pragma omp parallel for
    for (size_t i = 0; i < SIZE; i++) {
        c[i] = b[i] + a[i];
    }

    print_arr_sum(a, b, c, SIZE);
}
