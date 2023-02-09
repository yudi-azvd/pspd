#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "defs.h"

#define MAX_PROCS 32

// Assumindo que não haverá mais de MAX_PROCS processos
int job_division[MAX_PROCS] = {[0 ... MAX_PROCS - 1] = 0};
int job_offsets[MAX_PROCS] = {[0 ... MAX_PROCS - 1] = 0};

// PID   0  1  2  3
// jobs [2, 2, 2, 1]
int divide_jobs_and_offsets(int jobs, int num_workers) {
    int remaing_jobs = jobs, i = 0;
    while (remaing_jobs-- > 0) {
        job_division[i++ % num_workers]++;
    }

    int offset = 0;
    for (int i = 1; i < num_workers; i++) {
        offset += job_division[i - 1];
        job_offsets[i] = offset;
    }

    return 0;
}

void print_job_division(int num_workers) {
    for (int i = 0; i < num_workers; i++) {
        printf("J PID %d: %d jobs\n", i + 1, job_division[i]);
    }
}

void print_job_offsets(int num_workers) {
    for (int i = 0; i < num_workers; i++) {
        printf("O PID %d: offset %d\n", i + 1, job_offsets[i]);
    }
}

#endif // UTIL_H_INCLUDED