// https://stackoverflow.com/questions/9864510/struct-serialization-in-c-and-transfer-over-mpi
#include <mpi/mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../lib/darray.h"
#include "../lib/util.h"

int main(int argc, char** argv) {
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

        printf("Client\n");
        fclose(fp);
    } else {
        printf("Worker...\n");
    }

    return 0;
}