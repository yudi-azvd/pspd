// https://stackoverflow.com/questions/9864510/struct-serialization-in-c-and-transfer-over-mpi
#include <mpi/mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_BUFFER_SIZE 10'000'000
#define MAX_BUFFER_READ MAX_BUFFER_SIZE
#define MIN_BUFFER_READ 128

int main(int argc, char** argv) {
    char buffer[10] = "\0";
    int rank = -1, nworkers = 0;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_rank(MPI_COMM_WORLD, &nworkers);

    char* file_path = argv[1];
    if (rank == 0) {
        FILE* fp = fopen(file_path, "r");
        if (!fp) {
            printf("Error opening file %s\n", file_path);
            exit(1);
        }

        size_t buffer_size = MIN_BUFFER_READ;
        int i = 1, target_worker = 1;
        while (fgets(buffer, buffer_size, fp) != NULL) {
            target_worker = (target_worker + 1) % nworkers;
            buffer_size++;
        }        

        printf("Client\n");
        fclose(fp);
    } else {
        printf("Worker...\n");
    }

    return 0;
}