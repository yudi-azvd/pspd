#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#define BYTES_PER_LINE 9

#define MAX_PROCS 20

// Assumindo que não haverá mais de 8 threads
int job_division[MAX_PROCS] = {[0 ... MAX_PROCS - 1] = 0};
int job_offsets[MAX_PROCS] = {[0 ... MAX_PROCS - 1] = 0};

int get_file_size(char* filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        printf("Could not read file size: %s\n", filename);
        exit(1);
    }

    fseek(fp, 0L, SEEK_END);
    int size = ftell(fp);
    fclose(fp);
    return size;
}

// PID   0  1  2  3
// jobs [2, 2, 2, 1]
int divide_jobs_and_offsets(int jobs, int num_threads) {
    int remaing_jobs = jobs, i = 0;
    while (remaing_jobs-- > 0) {
        job_division[i++ % num_threads]++;
    }

    int offset = 0;
    for (int i = 1; i < num_threads; i++) {
        offset += job_division[i - 1] * BYTES_PER_LINE;
        job_offsets[i] = offset;
    }

    return 0;
}

void print_job_division(int num_threads) {
    for (int i = 0; i < num_threads; i++) {
        printf("        Jobs PID %d: %d jobs\n", i + 1, job_division[i]);
    }
}

void print_job_offsets(int num_threads) {
    for (int i = 0; i < num_threads; i++) {
        printf(" Offsets PID %d: offset %d\n", i + 1, job_offsets[i]);
    }
}

#endif // UTIL_H_INCLUDED