#include <omp.h>
#include <stdio.h>

int main() {
#pragma omp parallel num_threads(3)
    {
        int id = omp_get_thread_num();
        printf("Hello World %d\n", id);
    }
}
