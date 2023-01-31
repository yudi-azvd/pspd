#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    const int max_size = 1000000;
    int arr[max_size];
    int ocurrences = 0, current;
    int n = 3;

    for (int i = 0; i < max_size; i++) {
        scanf("%d", &current);
        arr[i] = current;
    }

#pragma omp parallel for reduction(+:ocurrences)
    for (int i = 0; i < max_size; i++) {
        if (arr[i] == n) {
            ocurrences++;
        }
    }

    printf("Found %d ocurrences\n", ocurrences);
    return 0;
}