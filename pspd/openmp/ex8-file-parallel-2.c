#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

// grep -E "0{7}+3" aleatorio.in | wc -l
// dd if=aleatorio.in skip=1955142 count=9 ibs=1
// cat out.o | grep -E "read number:\s+3\s" | sort | uniq | sed -r -E -e "s/^.*\s+([0-9]+)-byte.*$/\1/g" > addrs.out
// cat addrs.out | while read line; do dd if=aleatorio.in skip=$line count=9 ibs=1 status=none; done

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
    if (argc < 3) {
        printf("Usage: %s <num threads> <filename>", argv[0]);
        exit(1);
    }

    char* filename = argv[2];
    omp_set_num_threads(atoi(argv[1]));
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
        int offset = displc * tid;
        int read_number = 0;
        int local_ocurrences = 0;
        fseek(fp, offset, SEEK_SET);
        printf("(%d) offset = %8d | end: %d | displc: %d\n", tid, offset, offset + displc, displc);

        /**
         * FIXME: se filename=="aleatorio.in", a divisão
         * displc = file_size_bytes / omp_get_max_threads() NÃO É INTEIRA!!!
         */
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