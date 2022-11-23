#include <stdio.h>
// #include </mpi.h>
#include <mpi/mpi.h>
#include <string.h>

int main(int argc, char *argv[]) {
  int meurank, nprocs;
  char msg[100];
  MPI_Status status;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &meurank);
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

  if (meurank != 0) {
    sprintf(msg, "I'm alive");
    MPI_Send(msg, strlen(msg) + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
  } else {
    for (int i = 1; i < nprocs; i++) {
      MPI_Recv(msg, 100, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD,
               &status);
      printf("Processo %d enviou a mensagem --> %s\n", status.MPI_SOURCE, msg);
    }
  }

  MPI_Finalize();
  return 0;
}
