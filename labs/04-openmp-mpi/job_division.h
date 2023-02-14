#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "defs.h"

#define MAX_WORKERS 32

/**
 * Esse módulo assume que não haverá mais de MAX_WORKERS workers.
 *
 * WID: worker ID
 */

int job_division[MAX_WORKERS] = {[0 ... MAX_WORKERS - 1] = 0};
int job_offsets[MAX_WORKERS] = {[0 ... MAX_WORKERS - 1] = 0};

// WID   0  1  2  3
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
        printf("J WID %d: %d jobs\n", i + 1, job_division[i]);
    }
}

void print_job_offsets(int num_workers) {
    for (int i = 0; i < num_workers; i++) {
        printf("O WID %d: offset %d\n", i + 1, job_offsets[i]);
    }
}

#endif // UTIL_H_INCLUDED