#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

void print_arr(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("! Thread %d: %d times\n", i, arr[i]);
    }
    printf("\n");
}

int main(int argc, char* argv[]) {
    int max_threads = omp_get_max_threads();
    int vet[max_threads];
    memset(vet, 0, 4 * max_threads);
    // int ieth_thread;

#pragma omp parallel for
    for (int i = 0; i < MAX; i++) {
        int ieth_thread = omp_get_thread_num();
        // ieth_thread = omp_get_thread_num();
        printf("# Thread(%d) olá mundo\n", ieth_thread);
        vet[ieth_thread]++;
    }

    print_arr(vet, max_threads);
    printf("Max threads %d\n", max_threads);
}
