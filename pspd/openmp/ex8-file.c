#include <stdio.h>

// demora um pouco
// for((i=0;i<1000000;i++)); do printf "%0.8d\n" $RANDOM; done > aleatorio.in
//  grep 00000003 aleatorio.in | wc -l

int main() {
    const int max_size = 1000000;
    int n = 3;
    int current = 0, ocurrences = 0;

    for (int i = 0; i < max_size; i++) {
        scanf("%d", &current);
        if (current == n) {
            ocurrences++;
        }
    }

    printf("Found %d ocurrences\n", ocurrences);
    return 0;
}