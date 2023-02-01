#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

// grep -E "0{7}+3" aleatorio.in | wc -l
// dd if=aleatorio.in skip=1955142 count=9 ibs=1
// cat out.o | grep -E "read number:\s+3\s" | sort | uniq | sed -r -E -e "s/^.*\s+([0-9]+)-byte.*$/\1/g" > addrs.out
// cat addrs.out | while read line; do dd if=aleatorio.in skip=$line count=9 ibs=1 status=none; done

#define BYTES_PER_LINE 9

#define MAX_THREADS 8

// Assumindo que não haverá mais de 8 threads
int job_division[MAX_THREADS] = {[0 ... MAX_THREADS - 1] = 0};
int job_offsets[MAX_THREADS] = {[0 ... MAX_THREADS - 1] = 0};

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

// TID   0  1  2  3
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
        printf("        Jobs TID %d: %d jobs\n", i, job_division[i]);
    }
}

void print_job_offsets(int num_threads) {
    for (int i = 0; i < num_threads; i++) {
        printf(" Offsets TID %d: offset %d\n", i, job_offsets[i]);
    }
}

int main(int argc, char** argv) {
    int ocurrences = 0;
    if (argc < 3) {
        printf("Usage: %s <num threads> <filename>", argv[0]);
        exit(1);
    }

    omp_set_num_threads(atoi(argv[1]));
    char* filename = argv[2];

    const int num_threads = omp_get_max_threads();
    int file_size_bytes = get_file_size(filename);
    int jobs = file_size_bytes / BYTES_PER_LINE;
    int n = 3;

    divide_jobs_and_offsets(jobs, num_threads);

    // print_job_division(num_threads);
    // print_job_offsets(num_threads);
    // printf("        Jobs: %d\n", jobs);
    // printf("   File size: %d bytes\n", file_size_bytes);

#pragma omp parallel
    {
        FILE* fp = fopen(filename, "r");
        int tid = omp_get_thread_num();
        int displc = job_division[tid] * BYTES_PER_LINE;
        // int offset = displc * tid;
        // FIXME: descobrir como calcular esse offset
        int offset = job_offsets[tid];
        int read_number = 0;
        int local_ocurrences = 0;
        fseek(fp, offset, SEEK_SET);
        // printf("(%d) offset = %8d | end: %d | jobs: %d\n", tid, offset, offset + displc, displc);

        for (int i = 0; i < displc; i += BYTES_PER_LINE) {
            fseek(fp, offset + i, SEEK_SET);
            int bytes_read = fscanf(fp, "%d", &read_number);
            // printf("%d i=%8d %8d-byte read number: %8d | bytes read: %d\n", tid, i, offset + i, read_number, bytes_read);
            // printf("%d %8d-byte read number: %8d | bytes read: %d\n", tid, offset + i, read_number, bytes_read);
            if (read_number == n) {
                local_ocurrences++;
            }
        }

#pragma omp atomic
        ocurrences += local_ocurrences;

        // printf("[%d] read number: %8d | offset = %d\n", tid, read_number, offset);

        fclose(fp);
    }

    printf("Found %d ocurrences\n", ocurrences);
    return 0;
}