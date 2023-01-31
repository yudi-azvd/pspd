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

    char* filename = argv[1];
    int file_size_bytes = get_file_size(filename);
    int displc = file_size_bytes / omp_get_max_threads();
    int ocurrences = 0;
    int n = 3;

    // printf("File size: %d bytes\n", file_size_bytes);
    // printf("Displacement: %d\n\n", displc);

#pragma omp parallel shared(n, filename, displc)
    {
        FILE* fp = fopen(filename, "r");
        int tid = omp_get_thread_num();
        int offset = displc * tid;
        int read_number;
        fseek(fp, offset, SEEK_SET);

#pragma omp for private(read_number) reduction(+ : ocurrences)
        for (size_t i = 0; i < offset + displc; i++) {
            fscanf(fp, "%d", &read_number);
            if (read_number == n) {
                ocurrences++;
            }
        }

        // printf("[%d] read number: %8d | offset = %d\n", tid, read_number, offset);

        fclose(fp);
    }

    printf("Found %d ocurrences\n", ocurrences);

    return 0;
}