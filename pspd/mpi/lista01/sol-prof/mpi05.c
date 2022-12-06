#include <stdio.h>
#include <unistd.h>
#include <mpi.h>
#define TAMVET 5

int main(int argc, char **argv) {
    int rank, nprocs, i, j;
    int vetor[TAMVET], vbase[TAMVET];
    MPI_Status  status;

    for (i=0; i<TAMVET; i++) {
        vbase[i]=i+2;
    }
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    if (rank == 0) {
        for (i=1; i<nprocs; i++) {
            printf("Master[0] --> Escravo[%d]: ", i);
            for (j=0;j<TAMVET;j++) {
                vetor[j]=vbase[j]*i;
                printf("%d ", vetor[j]);
            }
            printf("\n");
            MPI_Send(vetor, TAMVET, MPI_INT, i, 1, MPI_COMM_WORLD);
        }
        for (i=1; i<nprocs; i++) {
            MPI_Recv(vetor, TAMVET, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            printf("Escravo[%d] --> Master[0]: ", status.MPI_SOURCE);
            for (j=0; j<TAMVET; j++) {
                printf("%d ", vetor[j]);
            }
            printf("\n");
        }
    } else {
        MPI_Recv(vetor, TAMVET, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for (j=0; j<TAMVET; j++) {
            vetor[j]=vetor[j] - 1;
        }
        MPI_Send(vetor, TAMVET, MPI_INT, 0, 1, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}
