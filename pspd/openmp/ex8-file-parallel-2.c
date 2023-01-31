#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

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

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Usage: %s <filename>", argv[0]);
        exit(1);
    }

    omp_set_num_threads(2);
    char* filename = argv[1];
    int file_size_bytes = get_file_size(filename);
    int displc = file_size_bytes / omp_get_max_threads();
    int ocurrences = 0;
    int n = 3;
    int BYTES_PER_LINE = 9;

    printf("File size: %d bytes\n", file_size_bytes);
    printf("Displacement: %d\n\n", displc);

#pragma omp parallel
    {
        FILE* fp = fopen(filename, "r");
        int tid = omp_get_thread_num();
        // printf("Thread %d\n", tid);
        int offset = displc * tid;
        int read_number = 0;
        int local_ocurrences = 0;
        fseek(fp, offset, SEEK_SET);
        printf("(%d) offset = %4d | displac: %d | end: %d\n", tid, offset, displc, offset + displc);

        for (int i = 0; i < offset + displc; i += BYTES_PER_LINE) {
            /**
             * FIXME: a TID 1 continua lendo mesmo dps de i > 180 (offs + displc)
             * 1 162-byte read number:    20416 | bytes read: 1
             * 1 171-byte read number:     9404 | bytes read: 1
             * 1 180-byte read number:     9404 | bytes read: -1
             * 1 189-byte read number:     9404 | bytes read: -1
             */
            fseek(fp, offset + i, SEEK_SET);
            int bytes_read = fscanf(fp, "%d", &read_number);
            printf("%d %3d-byte read number: %8d | bytes read: %d\n", tid, offset + i, read_number, bytes_read);
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