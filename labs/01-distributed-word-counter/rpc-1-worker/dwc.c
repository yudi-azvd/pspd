#include <stdio.h>

// mpirun $(pwd)/dwc

int main(int argc, char **argv) {
    int nprocs;

    MPI_Init(&argc, &argv);
    printf("hello world\n");
    MPI_Finalize();
}