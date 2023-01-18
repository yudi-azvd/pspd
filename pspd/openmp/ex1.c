#include <omp.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    omp_set_num_threads(6);
#pragma omp parallel
    {
        for (int i = 0; i < 3; i++) {
            printf("Thread(%d) olá mundo\n", omp_get_thread_num());
        }
    }
}
