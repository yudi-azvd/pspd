#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

int main() {
    int v[SIZE];
    int start = 0, end = 0, offset;

    for (int i = 0; i < SIZE; i++) {
        v[i] = i;
    }

#pragma omp parallel
    {
        while (end < SIZE) {
#pragma omp critical
            {
                offset = rand() % 15;
                offset = offset + start < SIZE ? offset : SIZE - offset;
                end = start + offset;

                int tid = omp_get_thread_num();
                printf("TID %d, start %3d, offset %3d, end %3d\n", tid, start, offset, end);

                for (int i = start; i < end; i++) {
                    printf("%d \n", v[i]);
                }

                start += offset;
            }
        }
    }
}