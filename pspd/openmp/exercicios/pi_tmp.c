/*

This program will numerically compute the integral of

                  4/(1+x*x)

from 0 to 1.  The value of this integral is pi -- which
is great since it gives us an easy way to check the answer.

The is the original sequential program.  It uses the timer
from the OpenMP runtime library

History: Written by Tim Mattson, 11/99.

*/
#include <omp.h>
#include <stdio.h>

static long num_steps = 1000000;
double step;

int main() {
    int i;
    double x, pi, sum = 0.0;
    double start_time, run_time;

    step = 1.0 / (double)num_steps;
    int threads = omp_get_max_threads();
    int jobs = num_steps / threads;

    start_time = omp_get_wtime();

#pragma omp parallel
    {
        // Vamos assumir que sempre vai ser 4
        int tid = omp_get_thread_num();
        int local_sum = 0;
        for (i = 1; i <= num_steps; i++) {
            x = (i - 0.5) * step;
            local_sum = local_sum + 4.0 / (1.0 + x * x);
        }

#pragma omp atomic
        sum += local_sum;
    }

    pi = step * sum;
    run_time = omp_get_wtime() - start_time;
    printf("\n pi with %ld steps is %f in %f seconds ", num_steps, pi, run_time);
}
