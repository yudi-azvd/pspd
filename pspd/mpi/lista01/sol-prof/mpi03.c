#include <stdio.h>
#include <mpi.h>

int main (int argc, char **argv){
    int		meurank, nprocs;
    int		voriginal=10, venvio, vrecebido;
    MPI_Status	status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &meurank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

    if (meurank == 0) {
        for (int i=1; i<nprocs; i++) {
            venvio=voriginal * i;
            MPI_Send(&venvio, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            printf("Master enviou %d para escravo[%d]\n", venvio, i);
            MPI_Recv(&venvio, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            printf("Master recebeu %d do escravo[%d]\n", venvio, status.MPI_SOURCE);
        }

    } else {
        MPI_Recv(&vrecebido, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Escravo[%d] recebeu %d do master\n", meurank, vrecebido);
        int valterado = vrecebido +2;
        MPI_Send(&valterado, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
