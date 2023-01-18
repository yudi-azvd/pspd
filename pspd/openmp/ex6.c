#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 1'000'000

void print_arr(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        printf(". Thread %d: %d\n", i, arr[i]);
    }
    printf("\n");
}

int main(int argc, char* argv[]) {
    omp_set_num_threads(4);
    int nthreads = omp_get_max_threads();
    int* executions = calloc(nthreads, sizeof(int));
    int ieth_thread, jobs = 100;

#pragma omp parallel for
    for (int i = 0; i < jobs; i++) {
        ieth_thread = omp_get_thread_num();
        printf("Thread(%d) olá mundo\n", ieth_thread);
        executions[ieth_thread]++;
    }

    printf("\n");
    printf("Initial Threads %d\n", nthreads);
    print_arr(executions, nthreads);
    free(executions);
}
