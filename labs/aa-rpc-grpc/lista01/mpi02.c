#include <stdio.h>
#include <mpi.h>

int main (int argc, char **argv){
    int meurank, nprocs;
    int voriginal=10, venvio, vrecebido;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &meurank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

    if (meurank == 0) {
        for (int i=1; i<nprocs; i++) {
            venvio=voriginal * i;
            MPI_Send(&venvio, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            printf("Master enviando %d para %d\n", venvio, i);
        }
    } else {
        MPI_Recv(&vrecebido, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Escravo[%d] recebeu %d\n", meurank, vrecebido);
    }

    MPI_Finalize();
    return 0;
}